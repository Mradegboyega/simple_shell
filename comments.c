#include "comments.h"
#include <stdio.h>
#include <string.h>

/**
 * remove_comments - Remove comments from a command.
 * @input: The input command.
 */
void remove_comments(char *input)
{
	char *comment_start;

	comment_start = strstr(input, "#");
	if (comment_start != NULL)
	{
		*comment_start = '\0';
	}
}
