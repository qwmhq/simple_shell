#include "shell.h"

/**
 * env_builtin - env builtin function
 *
 * @args: array of arguments
 * @status: holds exit status
 * @process_name: name of the shell process
 * @command_count: command count
 */
void env_builtin(char **args, int *status,
		char *process_name, int command_count)
{
	char **ptr =  environ;
	(void)(process_name);
	(void)(command_count);

	while (*ptr != NULL)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
	free_str_arr(args);
	*status = EXIT_SUCCESS;
}

/**
 * setenv_builtin - setenv builtin function
 *
 * @args: array of arguments
 * @status: holds exit status
 * @process_name: name of the shell process
 * @command_count: command count
 */
void setenv_builtin(char **args, int *status,
		char *process_name, int command_count)
{
	char **ptr =  args;
	int argcount = 0;

	while (*ptr != NULL)
	{
		argcount++;
		ptr++;
	}
	if (argcount != 3)
	{
		fprintf(stderr, "%s: %d: %s: Usage: %s VARIABLE VALUE\n",
				process_name, command_count, args[0], args[0]);
		*status = 2 << 8;
		free_str_arr(args);
		return;
	}
	if (setenv(args[1], args[2], 1) == -1)
	{
		perror(args[0]);
		*status = 2 << 8;
		free_str_arr(args);
		return;
	}
	free_str_arr(args);
	*status = EXIT_SUCCESS;
}

/**
 * unsetenv_builtin - unsetenv builtin function
 *
 * @args: array of arguments
 * @status: holds exit status
 * @process_name: name of the shell process
 * @command_count: command count
 */
void unsetenv_builtin(char **args, int *status,
		char *process_name, int command_count)
{
	char **ptr =  args;
	int argcount = 0;

	while (*ptr != NULL)
	{
		argcount++;
		ptr++;
	}
	if (argcount != 2)
	{
		fprintf(stderr, "%s: %d: %s: Usage: %s VARIABLE\n",
				process_name, command_count, args[0], args[0]);
		*status = 2 << 8;
		free_str_arr(args);
		return;
	}
	if (unsetenv(args[1]) == -1)
	{
		perror(args[0]);
		*status = 2 << 8;
		free_str_arr(args);
		return;
	}
	free_str_arr(args);
	*status = EXIT_SUCCESS;
}
