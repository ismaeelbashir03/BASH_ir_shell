#include "shell.h"

/**
 * new_process - create a new process
 * @args: array of strings that contains the command and its flags
 *
 * Return: 1 if success, 0 otherwise.
 */
int new_process(char **args) {
    pid_t pid;
    int status;

    // fork the process
    pid = fork();


    if (pid ==  0) {
        
        // if child, ignore SIGINT signal (allows for ctrl+c to kill the child process)
        signal(SIGINT, SIG_DFL);

        // if child, run the command (using execv'p' so we dont need full path)
        if (execvp(args[0], args) == -1) {
            char error_msg[DEFUALT_BUFFER_SIZE] = "Error in new_process \'";
            strcat(error_msg, args[0]);
            strcat(error_msg, "\'");
            perror(error_msg);
        }
        exit(EXIT_SUCCESS); // exit the child process
    }

    // if the fork fails, print error message
    else if (pid < 0) {
        perror("error in new_process: forking");
    }

    // if parent (BASH_ir), wait for the child process to finish
    else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    
    return EXIT_SUCCESS;
}

/**
 * execute_args - map if command is a builtin or a process
 * @args: command and its flags
 *
 * Return: 1 on sucess, 0 otherwise
 */
int execute_args(char **args) {

    // list of builtin functions and their names
    char *builtin_func_list[] = {
    "ls",
    "cd",
    "help",
    "exit"
    };

    int (*builtin_func[])(char **) = {
        &own_ls,
        &own_cd,
        &own_help,
        &own_exit
    };

    // ignore empty commands
    if (args[0] == NULL)
    {
        return EXIT_SUCCESS;
    }

    // if the command is a builtin, execute it
    int builtin_func_list_size = sizeof(builtin_func_list) / sizeof(char *);
    for (int i = 0; i < builtin_func_list_size; i++) {
        if (strcmp(args[0], builtin_func_list[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }
    
    // otherwise, execute a new process from the command
    return new_process(args);
}