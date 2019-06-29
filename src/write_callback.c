#include "chunks.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr)userdata;
	xmlParseChunk(ctxt, ptr, size*nmemb, 0);

	return size*nmemb;
}
