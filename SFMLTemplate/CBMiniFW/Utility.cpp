#include "Utility.h"
using namespace cbmini;
using namespace cbfw;


#include <stdio.h>
#include <malloc.h>


// file loader
char *Utility::LoadFile(const char *filePath)
{
	if (filePath)
	{
		FILE *fp = fopen(filePath, "rb");
		if (fp)
		{
			// count the number of characters
			fseek(fp, 0, SEEK_END);
			int count = (int)ftell(fp);
			char *contents = AllocString(count+1);
			if (contents)
			{
				rewind(fp);
				count = (int)fread(contents, 1, count, fp);
				*(contents+count) = 0;	// null-terminate
				return contents;
			}
		}
	}
	return 0;
}


// allocate string
char *Utility::AllocString(const unsigned int size)
{
	if (size)
		return (char *)malloc(size);
	return 0;
}


// free string
void Utility::FreeString(char *str)
{
	free(str);
}
