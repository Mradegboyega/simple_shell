#include "path_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <unistd.h>

/**
 * find_command_in_path - Find a command in the PATH
 * @command: The command to find
 * @path: The PATH environment variable
 * @full_path: Buffer to store the full path of the command
 * @buf_size: The size of the buffer
 * Return: 0 on success, -1 on failure
 */
int find_command_in_path(char *command, char *path, char *full_path, size_t buf_size)
{
	char *path_copy = strdup(path);
	char *token;

	if (path_copy == NULL)
	{
		perror("Error");
		return (-1);
	}

	for (token = strtok(path_copy, ":"); token != NULL; token = strtok(NULL, ":"))
	{
		if (snprintf(full_path, buf_size, "%s/%s", token, command) >= (int)buf_size)
		{
			fprintf(stderr, "Error: Full path exceeds buffer size.\n");
			free(path_copy);
			return (-1);
		}

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (0);
		}
	}

	free(path_copy);
	fprintf(stderr, "Error: Command not found in PATH.\n");
	return (-1);
}
