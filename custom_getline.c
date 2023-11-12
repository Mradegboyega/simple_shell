#include "custom_getline.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE 1024

/**
 * custom_getline - Read a line from standard input.
 *
 * Return: A dynamically allocated string containing the line.
 */
char *custom_getline(void)
{
	char buffer[READ_SIZE];
	static int position;
	static int bytes_read;
	char *line = NULL;
	int line_length = 0;

	while (1)
	{
		if (position >= bytes_read)
		{
			position = 0;
			bytes_read = read(STDIN_FILENO, buffer, READ_SIZE);

			if (bytes_read == 0)
			{
				free(line);
				return (NULL);
			}
			else if (bytes_read < 0)
			{
				perror("Read error");
				free(line);
				return (NULL); /* Read error */
			}
		}

		if (buffer[position] == '\n')
		{
			line = (char *)realloc(line, line_length + 1);
			if (line == NULL)
			{
				perror("Memory allocation error");
				free(line);
				return (NULL); /* Memory allocation error */
			}
			line[line_length] = '\0';
			return (line); /* Line read successfully */
		}

		line = (char *)realloc(line, line_length + 1);
		if (line == NULL)
		{
			perror("Memory allocation error");
			free(line);
			return (NULL); /* Memory allocation error */
		}
		line[line_length] = buffer[position];
		line_length++;
		position++;
	}
}
