#include "shell.h"

/**
 * _getenv - get an environment variable
 *
 * @name: name of the variable to get
 * Return: pointer to the value of the environment variable,
 *			or NULL if not found
 */
char *_getenv(const char *name)
{
	char **ptr = environ, *cmp;
	int len = strlen(name);

	cmp = malloc(len + 2);
	strcpy(cmp, name);
	cmp[len] = '=';
	cmp[len + 1] = '\0';
	while (*ptr)
	{
		if (strncmp(*ptr, cmp, len + 1) == 0)
		{
			free(cmp);
			return (*ptr + len + 1);
		}
		ptr++;
	}
	free(cmp);
	return (NULL);
}
