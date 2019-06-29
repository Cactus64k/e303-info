#include "chunks.h"

REPLACE_LIST* parse_replace_file(char* file_name)
{
	FILE* f = fopen(file_name, "rb");
	REPLACE_LIST* list = NULL;
	if(f != NULL)
	{
		char buff[512];

		while(1)
		{
			if(read_line(buff, sizeof(buff), f) == EXIT_SUCCESS)
			{
				char* ch = strchr(buff, ':');
				if(ch != NULL)
				{
					*ch = '\0';
					char* original = buff;
					char* replace = ch+1;

					list = replace_list_add_new(list, original, replace);
				}
			}
			else
				break;
		}

		fclose(f);
	}

	return list;;
}

REPLACE_LIST* replace_list_add_new(REPLACE_LIST* item, char* original, char* replace)
{
	REPLACE_LIST* new_item = malloc(sizeof(REPLACE_LIST));

	new_item->next		= item;
	new_item->original	= strdup(original);
	new_item->replace	= strdup(replace);

	return new_item;
}

void replace_list_free(REPLACE_LIST* item)
{
	while(item != NULL)
	{
		REPLACE_LIST* next = item->next;

		free(item->original);
		free(item->replace);
		free(item);

		item = next;
	}
}

REPLACE_LIST* replace_list_search(REPLACE_LIST* list, char* original)
{
	while(list != NULL)
	{
		if(strcmp(list->original, original) == 0)
			return list;

		list = list->next;
	}

	return NULL;
}
