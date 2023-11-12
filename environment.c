#include "environment.h"
#include <stdio.h>
#include <unistd.h>

/**
 * print_environment - Print the current environment variables
 */
void print_environment(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
