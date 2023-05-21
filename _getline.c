#include "shell.h"

/**
 * _getline - get a single line from a stream
 *
 * @lineptr: buffer to read into
 * @n: size of lineptr
 * @stream: the stream to read from
 *
 * Return: number of bytes read
 */
int _getline(char **lineptr, size_t *n, FILE *stream)
{
	int buf_idx = 0, buf_size = 100;
	char c, *temp_buf;

	if (*lineptr == NULL && *n == 0)
	{
		*lineptr = malloc(buf_size);
		if (*lineptr == NULL)
			return (-1);
		*n = buf_size;
	}

	c = fgetc(stream);
	if (c == EOF)
		return (-1);
	(*lineptr)[buf_idx++] = c;
	if (c == '\n')
	{
		(*lineptr)[buf_idx] = '\0';
		return (buf_idx);
	}

	while ((c = fgetc(stream)) != EOF)
	{
		if (buf_idx > buf_size - 2)
		{
			temp_buf = realloc(*lineptr, (buf_size += 100));
			if (temp_buf == NULL)
				exit(98);
			*lineptr = temp_buf;
			*n = buf_size;
		}
		(*lineptr)[buf_idx++] = c;

		if (c == '\n')
			break;
	}
	(*lineptr)[buf_idx] = '\0';

	return (buf_idx);
}
