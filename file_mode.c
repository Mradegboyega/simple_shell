#include "file_mode.h"
#include "execute.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ; /* Declare environ as an external variable */

/**
 * execute_file_commands - Execute commands from a file
 * @file: The file containing commands
 */
void execute_file_commands(FILE *file)
{
	char buffer[1024];
	char *replaced_command;
	int line_number = 1;
	int result;

	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		replaced_command = replace_variables(buffer, 0);

		if (replaced_command == NULL)
		{
			fprintf(stderr, "Error replacing variables on line %d.\n", line_number);
			exit(EXIT_FAILURE);
		}

		result = execute_command(replaced_command, environ); /* Pass environ as the environment variable array */
		free(replaced_command);

		if (result == -1)
		{
			fprintf(stderr, "Error executing command on line %d.\n", line_number);
			exit(EXIT_FAILURE);
		}

		line_number++;
	}
}
