#include "exit.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * exit_shell - Exits the shell gracefully
 * @status: The exit status
 */
void exit_shell(int status)
{
	exit(status);
}
