#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * replace_variables - Replace special variables in a command string
 * @command: The command string
 * @last_status: The exit status of the last command
 * Return: A newly allocated string with replaced variables, or NULL on failure
 */
char *replace_variables(char *command, int last_status)
{
	char buffer[64];
	char *variable;
	char *result = strdup(command);

	if (result == NULL)
	{
		perror("Error");
		return (NULL);
	}

	/* Replace $$ with the process ID */
	variable = strstr(result, "$$");
	if (variable != NULL)
	{
		snprintf(buffer, sizeof(buffer), "%d", getpid());
		result = replace_string(result, "$$", buffer);
	}

	/* Replace $? with the exit status of the last command */
	variable = strstr(result, "$?");
	if (variable != NULL)
	{
		snprintf(buffer, sizeof(buffer), "%d", last_status);
		result = replace_string(result, "$?", buffer);
	}

	return (result);
}

/**
 * replace_string - Replace occurrences of a substring in a string
 * @str: The original string
 * @old: The substring to replace
 * @new: The replacement substring
 * Return: A newly allocated string with replaced occurrences, or NULL on failure
 */
char *replace_string(const char *str, const char *old, const char *new)
{
	char *result;
	int new_len = strlen(new);
	int old_len = strlen(old);
	int count = 0;
	int i = 0;

	/* Count the occurrences of the substring to replace */
	for (i = 0; str[i] != '\0'; i++)
	{
		if (strstr(&str[i], old) == &str[i])
		{
			count++;
			i += old_len - 1;
		}
	}

	/* Allocate memory for the new string */
	result = (char *)malloc(strlen(str) + count * (new_len - old_len) + 1);
	i = 0; /* Reuse i */

	/* Replace occurrences of the substring */
	for (i = 0; str[i] != '\0'; i++)
	{
		if (strstr(&str[i], old) == &str[i])
		{
			strcpy(&result[i], new);
			i += new_len - 1;
		}
		else
		{
			result[i] = str[i];
		}
	}
	result[i] = '\0';

	return (result);
}
