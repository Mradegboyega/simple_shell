#include <stdlib.h>
#include <string.h>

char *my_strdup(const char *str)
{
	size_t len = strlen(str);
	char *new_str = (char *)malloc(len + 1);
	if (new_str)
	{
		strcpy(new_str, str);
	}
	return (new_str);
}
