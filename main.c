#include "shell.h"

/**
 * main - main program execution
 *
 * @argc: argument count
 * @argv: null-terminated array of argument values
 *
 * Return: exit code of the last command executed
 */
int main(int argc, char **argv)
{
	unsigned int command_count = 0;
	int status = 0;

	(void)(argc);
	while (1)
	{
		void (*builtin_func)(char **, int *, char *, int);
		char *line = NULL, *abs_path = NULL, **args = NULL;
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
		free(line);
		if (args == NULL || *args == NULL)
		{
			continue;
		}
		builtin_func = find_in_builtins(args[0]);
		if (builtin_func != NULL)
		{
			builtin_func(args, &status, argv[0], command_count);
			continue;
		}
		abs_path = strchr(args[0], '/') ? strdup(args[0]) : find_in_path(args[0]);
		if (abs_path == NULL)
		{
			fprintf(stderr, "%s: %u: %s: not found\n", argv[0], command_count, args[0]);
			status = 127 << 8;
		} else
		{
			fork_exec_wait(abs_path, args, environ, &status, argv[0]);
			free(abs_path);
		}
		free_str_arr(args);
	}
	return (WEXITSTATUS(status));
}
