#include "shell.h"

/**
 * find_in_path - find a file in PATH
 *
 * @filename: name of the file to find
 *
 * Return: pointer to a string containing the absolute path,
 *			or NULL if the file was not found in PATH
 */
char *find_in_path(const char *filename)
{
	char *path = _getenv("PATH"), *ptr = path;

	while (*ptr)
	{
		char *abs_path;
		unsigned int dir_len = 0;
		struct stat st;

		if (*ptr == ':')
		{
			ptr++;
			continue;
		}

		while (*ptr != ':' && *ptr != '\0')
		{
			dir_len++;
			ptr++;
		}
		ptr -= dir_len;

		abs_path = malloc(dir_len + strlen(filename) + 1);
		strncpy(abs_path, ptr, dir_len);
		if (abs_path[dir_len - 1] != '/')
		{
			abs_path[dir_len] = '/';
			strcpy(abs_path + dir_len + 1, filename);
		}
		else
			strcpy(abs_path + dir_len, filename);
		if (stat(abs_path, &st) == 0)
		{
			return (abs_path);
		}
		ptr += dir_len;
		free(abs_path);
	}
	return (NULL);
}
