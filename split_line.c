#include "shell.h"

/**
 * copy_word_to_buffer - copy a word to a new string
 *
 * @str: pointer to the beginning of the word
 * @dest: buffer to copy the word to
 *
 * Return: length of the word copied
 */
int copy_word_to_buffer(char *str, char **dest)
{
	int i, len = 0;

	while (*(str + len) != ' ' && *(str + len) != '\n')
		len++;
	*dest = malloc((len + 1) * sizeof(char));
	if (*dest == NULL)
		return (-1);
	for (i = 0; i < len; i++)
		*(*(dest) + i)  = *(str + i);
	*(*(dest) + len) = '\0';

	return (len);
}

/**
 * split_line - split line to array of words
 *
 * @line: string
 *
 * Return: array containing the split line
 */
char **split_line(char *line)
{
	char *ptr, **arr;
	unsigned int current_arg = 0, arg_count = 0;

	ptr = line;
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\n' && *ptr != '\0' &&
				(*(ptr + 1) == ' ' || *(ptr + 1) == '\n' || *(ptr + 1) == '\0'))
			arg_count++;
		ptr++;
	}
	if (arg_count < 1)
		return (NULL);
	arr = malloc((arg_count + 1) * sizeof(char *));
	if (arr == NULL)
		exit(EXIT_FAILURE);
	arr[arg_count] = NULL;

	ptr = line;
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\n')
			ptr += copy_word_to_buffer(ptr, &arr[current_arg++]);
		else
			ptr++;
	}
	return (arr);
}

/**
 * free_str_arr - free an array of strings
 *
 * @arr: pointer to the array. must be null terminated
 */
void free_str_arr(char **arr)
{
	char **ptr = arr, **temp;

	while (*ptr != NULL)
	{
		temp = ptr;
		ptr++;
		free(*temp);
	}
	free(arr);
}
