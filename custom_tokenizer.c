#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_tokenizer.h"
#include "my_strdup.h"

/**
 * custom_tokenizer - Tokenize a string.
 * @str: The input string.
 * @delim: The delimiter string.
 * @tokens: An array of strings to store the tokens.
 * @max_tokens: The maximum number of tokens.
 *
 * Return: The number of tokens found.
 */
int custom_tokenizer(const char *str, const char *delim, char *tokens[], int max_tokens)
{
	char *mutable_str;
	char *token;
	int token_count = 0;

	if (str == NULL || tokens == NULL || max_tokens <= 0)
	{
		return (-1);
	}

	mutable_str = my_strdup(str); /* Create a non-constant copy of the string */

	if (mutable_str == NULL)
	{
		return (-1);
	}

	token = strtok(mutable_str, delim);

	while (token != NULL && token_count < max_tokens)
	{
		tokens[token_count] = token;
		token_count++;
		token = strtok(NULL, delim);
	}

	free(mutable_str); /* Remember to free the allocated memory */

	return (token_count);
}
