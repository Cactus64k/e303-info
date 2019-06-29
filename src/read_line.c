#include "chunks.h"

int read_line(char* buff, size_t buff_size, FILE* f)
{
	char read_buff[16];
	size_t buff_pos = 0;
	bool file_end = false;

	while((buff_size > buff_pos) && file_end == false)
	{
		size_t count = fread(read_buff, 1, sizeof(read_buff), f);
		file_end = (count == sizeof(buff))?false: true;
		count = (buff_size > buff_pos + count)?count: buff_size-buff_pos;

		for(size_t i=0; i<count; i++)
		{
			if(read_buff[i] == '\n')
			{
				buff[buff_pos] = 0;
				fseek(f, i+1 - count, SEEK_CUR);

				return EXIT_SUCCESS;
			}
			else
				buff[buff_pos++] = read_buff[i];
		}
	}
	return EXIT_FAILURE;
}
