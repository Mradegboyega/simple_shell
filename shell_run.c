#include "shell_run.h"
#include "file_mode.h"
#include "variables.h"
#include "custom_tokenizer.h"
#include "execute.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

/**
 * print_prompt - Print the shell prompt.
 */
void print_prompt(void)
{
	printf("$ "); /* Basic prompt */
}

/**
 * execute_commands - Execute the given commands.
 * @command: A string containing the command to be executed.
 * Return: The exit status of the executed command.
 */
int execute_commands(const char *command)
{
	char *command_copy;
	char *tokens[10];
	char delimiter = ' ';
	int count;
	int result = 0;

	/* Check for empty commands */
	if (command == NULL || *command == '\0')
	{
		return (0);
	}

	/* Duplicate the command to avoid modification */
	command_copy = strdup(command);
	if (command_copy == NULL)
	{
		perror("Error");
		return (-1);
	}

	/* Tokenize the command */
	count = custom_tokenizer(command_copy, &delimiter, tokens, 10);
	free(command_copy);

	if (count > 0)
	{
		/* Check for built-in commands */
		if (strcmp(tokens[0], "exit") == 0)
		{
			/* Exit the shell */
			exit(0);
		}
		else if (strcmp(tokens[0], "cd") == 0)
		{
			/* Change directory */
			if (count > 1)
			{
				if (chdir(tokens[1]) != 0)
				{
					perror("Error changing directory");
					return (-1);
				}
			}
			else
			{
				/* Change to the home directory if no directory is specified */
				if (chdir(getenv("HOME")) != 0)
				{
					perror("Error changing directory");
					return (-1);
				}
			}
			return (0); /* Indicate success */
		}
		else if (strcmp(tokens[0], "pwd") == 0)
		{
			/* Print the current working directory */
			char cwd[1024];
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				printf("%s\n", cwd);
			}
			else
			{
				perror("Error");
				return (-1);
			}
		}
		else if (strcmp(tokens[0], "env") == 0)
		{
			/* Print environment variables */
			char **current_env = environ;
			while (*current_env != NULL)
			{
				printf("%s\n", *current_env);
				current_env++;
			}
		}
		else
		{
			/* Execute a command */
			result = execute_command(tokens[0], tokens); /* Pass tokens as an argument */
		}
	}
	return (result);
}

/**
 * run_shell - Run the shell.
 */
void run_shell(void)
{
	char *buffer = NULL;
	size_t buf_size = 0;
	ssize_t line_size;
	int last_status = 0;
	int result;

	/* Check if stdin is not a terminal */
	if (!isatty(STDIN_FILENO))
	{
		char *line = NULL;
		size_t len = 0;

		/* Read lines from stdin and execute commands */
		while (getline(&line, &len, stdin) != -1)
		{
			result = execute_commands(line);
			if (result == -1)
			{
				fprintf(stderr, "Error executing command.\n");
				last_status = 2;
			}
			else
			{
				last_status = result;
			}
		}

		free(line);
		exit(last_status);
	}

	/* Interactive shell loop */
	while (1)
	{
		print_prompt();

		line_size = getline(&buffer, &buf_size, stdin);
		if (line_size == -1)
		{
			printf("\n");
			break;
		}

		if (line_size > 0 && buffer[line_size - 1] == '\n')
			buffer[line_size - 1] = '\0';

		result = execute_commands(buffer);
		if (result == -1)
		{
			fprintf(stderr, "Error executing command.\n");
			last_status = 2;
		}
		else
		{
			last_status = result;
		}
	}

	free(buffer);
	exit(last_status);
}
