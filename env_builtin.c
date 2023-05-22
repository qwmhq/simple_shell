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
