#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROMPT "$ "

extern char **environ;

char *_getenv(const char *name);
int _getline(char **lineptr, size_t *n, FILE *stream);
char **split_line(char *line);
void free_str_arr(char **arr);
char *find_in_path(const char *filename);
int fork_exec_wait(char *pathname, char **argv, char **envp,
		int *status, char *err_str);


#endif
