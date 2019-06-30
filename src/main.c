#include "chunks.h"

int main(int argc, char *argv[])
{
	int status = EXIT_SUCCESS;

	if((argc != 3) && (argc != 4))
	{
		fprintf(stderr, "e303-info [url_address] [param] [replace file optional]\n\n");
		fprintf(stderr, "Replace file format:\n");
		fprintf(stderr, "original:replace\\n\n");
		fprintf(stderr, "original1:replace1\\n\n");

		status = EXIT_FAILURE;
	}
	else
	{
		char* url					= argv[1];
		char* param_name			= argv[2];
		REPLACE_LIST* replace_list	= NULL;

		if(argc == 4)
			replace_list = parse_replace_file(argv[3]);

		CURL* curl = curl_easy_init();
		xmlParserCtxtPtr ctxt = xmlCreatePushParserCtxt(NULL, NULL, NULL, 0, NULL);

		if(curl != NULL)
		{
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, ctxt);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

			CURLcode res = curl_easy_perform(curl);
			if(res == CURLE_OK)
			{
				xmlParseChunk(ctxt, NULL, 0, 1);

				if(ctxt->wellFormed == 1)
				{
					xmlDocPtr doc		= ctxt->myDoc;
					xmlNode* root		= xmlDocGetRootElement(doc);
					xmlNode* child		= root->children;
					xmlChar* content	= get_xml_node_content(child, param_name);

					if(content != NULL)
					{
						REPLACE_LIST* item = replace_list_search(replace_list, (char*)content);
						if(item != NULL)
							printf("%s\n", item->replace);
						else
							printf("%s\n", content);

					}

					xmlFree(content);
					xmlFreeDoc(doc);
				}
				else
				{
					fprintf(stderr, "ERROR: failed to parse xml\n");
					status = EXIT_FAILURE;
				}

			}
			else
			{
				fprintf(stderr, "ERROR: %s\n", curl_easy_strerror(res));
				status = EXIT_FAILURE;
			}
		}

		curl_easy_cleanup(curl);
		xmlFreeParserCtxt(ctxt);
		xmlCleanupParser();
		replace_list_free(replace_list);
	}

	return status;
}
