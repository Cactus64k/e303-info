
#ifndef CHUNKS_H_
	#define CHUNKS_H_

	#define _POSIX_C_SOURCE 200809L

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <assert.h>
	#include <stdbool.h>

	#include <libxml/parser.h>
	#include <libxml/tree.h>

	#include <curl/curl.h>


	xmlChar* get_xml_node_content(xmlNode* node, char* param);
	size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

	typedef struct REPLACE_LIST
	{
		char* original;
		char* replace;
		struct REPLACE_LIST* next;

	} REPLACE_LIST;

	REPLACE_LIST* replace_list_add_new(REPLACE_LIST* item, char* original, char* replace);
	REPLACE_LIST* replace_list_search(REPLACE_LIST* list, char* original);
	void replace_list_free(REPLACE_LIST* item);


	int read_line(char* buff, size_t buff_size, FILE* f);
	REPLACE_LIST* parse_replace_file(char* file_name);

#endif /* CHUNKS_H_ */
