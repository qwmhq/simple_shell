#include "shell.h"

/**
 * main - main program execution
 *
 * @argc: argument count
 * @argv: null-terminated array of argument values
 *
 * Return: 0 upon suceess
 */
int main(int argc, char **argv)
{
	unsigned int command_count = 0;
	int status;

	(void)(argc);
	while (1)
	{
		char *line = NULL, *abs_path, **args;
		size_t n = 0;
		ssize_t m;

		if (isatty(STDIN_FILENO))
			printf("%s", PROMPT);
		m = _getline(&line, &n, stdin);
		command_count++;
		if (m == -1)
		{
			free(line);
			break;
		}
		args = split_line(line);
		if (args == NULL || *args == NULL)
		{
			free(line);
			continue;
		}
		abs_path = strchr(args[0], '/') ? strdup(args[0]) : find_in_path(args[0]);
		if (abs_path == NULL)
		{
			fprintf(stderr, "%s: %u: %s: not found\n", argv[0], command_count, args[0]);
		} else
		{
			fork_exec_wait(abs_path, args, environ, &status, argv[0]);
			free(abs_path);
		}
		free(line);
		free_str_arr(args);
	}
	return (0);
}
