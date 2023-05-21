#include "shell.h"

/**
 * fork_exec_wait - fork the main process and execute a program
 *
 * @pathname: path of file to execute
 * @argv: array of pointers to strings,
 *			serves as command line args to the program
 * @envp: array of pointers to strings,
 *			serves as the environment variables of the program
 * @status: exit status of the program
 * @err_str: string to print in case of an error, err_str is
 *			passsed to perror
 *
 * Return: 0 on success, -1 on failure
 */
int fork_exec_wait(char *pathname, char **argv, char **envp,
		int *status, char *err_str)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(err_str);
		return (-1);
	}
	if (child_pid == 0)
	{
		if (execve(pathname, argv, envp) == -1)
		{
			perror(err_str);
			return (-1);
		}
	} else
	{
		wait(status);
	}
	return (0);
}
