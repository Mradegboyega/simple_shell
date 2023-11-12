#include "alias.h"
#include "custom_tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_strdup.h"

#define MAX_ALIASES 10

/**
 * add_alias - Add a new alias or update an existing one.
 * @aliases: Array of alias structures.
 * @alias_count: Number of existing aliases.
 * @name: Name of the alias.
 * @value: Value of the alias.
 *
 * Return: 0 on success, -1 on failure.
 */
int add_alias(Alias aliases[], int alias_count, char *name, char *value)
{
	int i;
	Alias new_alias;

	if (alias_count >= MAX_ALIASES)
	{
		fprintf(stderr, "Alias limit exceeded. Could not add alias.\n");
		return (-1);
	}

	/* Check if the alias already exists; update its value if it does. */
	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			free(aliases[i].value);
			aliases[i].value = my_strdup(value);
			if (aliases[i].value == NULL)
			{
				perror("Error");
				return (-1);
			}
			return (0);
		}
	}

	/* Create a new alias if it doesn't exist. */
	new_alias.name = my_strdup(name);
	if (new_alias.name == NULL)
	{
		perror("Error");
		return (-1);
	}

	new_alias.value = my_strdup(value);
	if (new_alias.value == NULL)
	{
		perror("Error");
		free(new_alias.name);
		return (-1);
	}

	/* Add the new alias to the array. */
	aliases[alias_count] = new_alias;
	return (0);
}

/**
 * list_aliases - Display all aliases.
 * @aliases: Array of alias structures.
 * @alias_count: Number of existing aliases.
 */
void list_aliases(Alias aliases[], int alias_count)
{
	int i;

	/* Display each alias in the array. */
	for (i = 0; i < alias_count; i++)
	{
		printf("alias %s='%s'\n", aliases[i].name, aliases[i].value);
	}
}
