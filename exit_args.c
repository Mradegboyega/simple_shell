#include "exit_args.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * exit_with_status - Exit the shell with a specified status
 * @status_str: The exit status as a string
 */
void exit_with_status(const char *status_str)
{
	int status = 0;

	if (status_str != NULL && *status_str != '\0')
	{
		status = atoi(status_str);
	}

	exit(status);
}
