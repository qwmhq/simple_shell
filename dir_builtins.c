#include "shell.h"

/**
 * cd_builtin - cd builtin
 *
 * @args: array of arguments
 * @status: exit status
 * @process_name: name of the shell process
 * @command_count: command count
 */
void cd_builtin(char **args, int *status,
		char *process_name, int command_count)
{
	char current_dir[512], *dir, **ptr = args;
	int argcount = 0;

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror(args[0]);
		*status = 1 << 8;
		return;
	}
	while (*ptr != NULL)
	{
		argcount++;
		ptr++;
	}
	if (argcount == 1)
	{
		dir = _getenv("HOME") != NULL ? _getenv("HOME") : current_dir;
	}
	else if (argcount > 1 && strcmp(args[1], "-") == 0)
	{
		dir = _getenv("OLDPWD") != NULL ? _getenv("OLDPWD") : current_dir;
		printf("%s\n", dir);
	}
	else
		dir = args[1];

	if (chdir(dir) == -1)
	{
		fprintf(stderr, "%s: %d: %s: can't cd to %s\n",
				process_name, command_count, args[0], dir);
		*status = 2 << 8;
	} else
	{
		setenv("OLDPWD", current_dir, 1);
		getcwd(current_dir, sizeof(current_dir));
		setenv("PWD", current_dir, 1);
		*status = EXIT_SUCCESS;
	}
	free_str_arr(args);
}

/**
 * pwd_builtin - pwd builtin
 *
 * @args: array of arguments
 * @status: exit status
 * @process_name: name of the shell process
 * @command_count: command count
 */
void pwd_builtin(char **args, int *status,
		char *process_name, int command_count)
{
	char current_dir[512];

	(void)(process_name);
	(void)(command_count);
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror(args[0]);
		*status = 1 << 8;
	}
	printf("%s\n", current_dir);
	*status = EXIT_SUCCESS;
	free_str_arr(args);
}
