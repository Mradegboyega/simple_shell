#include "arguments.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * execute_command_with_args - Execute a command with arguments.
 * @command: The command to execute.
 * @args: An array of arguments.
 *
 * Return: 0 for success, 1 for failure.
 */
int execute_command_with_args(const char *command, char **args)
{
	pid_t child_pid;
	int status;

	if (command == NULL || args == NULL || *command == '\0')
	{
		return (1); /* Invalid input */
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Fork failed");
		return (1);
	}

	if (child_pid == 0)
	{
		/* This is the child process */
		execvp(command, args);
		perror("Execution failed");
		exit(1);
	}
	else
	{
		/* This is the parent process */
		waitpid(child_pid, &status, 0);

		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		else
		{
			return (1);
		}
	}
}
