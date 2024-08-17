#ifndef SHELL_H

#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>


/*---DEFINES---*/
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define TOK_DELIM " \t\r\n\a"
#define DEFUALT_BUFFER_SIZE 1024


/*---PROTOTYPES---*/

// BASH_ir.c 
int isInteractive(void);

// input.c
char *getUserInput(void);
char **parseInput(char *input);

// execute.c
int execute_args(char **args);

// builtins.c
int own_cd(char **args);
int own_ls(char **args);
int own_env(char **args);
int own_help(char **args);
int own_exit(char **args);

#endif