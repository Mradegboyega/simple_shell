#include "execute.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - Execute a command with arguments
 * @command: The command to execute
 * @args: An array of arguments
 * Return: The exit status of the command
 */
int execute_command(const char *command, char *const args[])
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (-1);
	}

	if (child_pid == 0)
	{
		if (execvp(command, args) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

	return (0);
}
