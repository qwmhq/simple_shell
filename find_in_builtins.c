#include "shell.h"

void (*find_in_builtins(const char *command))(char **, int *, char *, int)
{
	builtin_t builtins[] = {
		{"exit", exit_builtin},
		{"env", env_builtin},
		{"setenv", setenv_builtin},
		{"unsetenv", unsetenv_builtin},
		{NULL, NULL}
	};
	builtin_t *ptr = builtins;

	while (ptr->command != NULL)
	{
		if (strcmp(ptr->command, command) == 0)
		{
			return (ptr->func);
		}
		ptr++;
	}
	return (NULL);
}
