#include "shell.h"

/**
 * exit_shell - exit builtin
 *
 * @args: array of arguments
 * @status: exit status
 * @process_name: name of the shell process
 * @command_count: command count
 */
void exit_builtin(char **args, int *status,
		char *process_name, int command_count)
{
	int exit_code;

	if (args[1] != NULL)
	{
		char *c = args[1];

		while (*c != '\0')
		{
			if (!isdigit(*c))
			{
				fprintf(stderr, "%s: %d: %s: Illegal number: %s\n",
						process_name, command_count, args[0], args[1]);
				*status = 2 << 8;
				return;
			}
			c++;
		}
		exit_code = atoi(args[1]);
	} else
	{
		exit_code = WEXITSTATUS(*status);
	}
	free_str_arr(args);
	exit(exit_code);
}
