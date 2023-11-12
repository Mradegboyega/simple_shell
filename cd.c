#include "cd.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * custom_cd - Change the current working directory.
 * @directory: The directory to change to.
 */
void custom_cd(const char *directory)
{
	if (directory == NULL)
	{
		fprintf(stderr, "Usage: cd [DIRECTORY]\n");
		return;
	}

	if (chdir(directory) == -1)
	{
		perror("Error changing directory");
	}
}

