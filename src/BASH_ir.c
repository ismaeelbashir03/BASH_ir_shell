#include "shell.h"

/*
 * Check if the shell is running in interactive mode
 * 
 * Using isatty() function to check if the file descriptor is associated with a terminal
 * File descriptors: 0, 1 and 2 are for stdin, stdout and stderr respectively
 */
int isInteractive() {
    return isatty(STDIN_FILENO);
}

/*
 * Print the shell prompt
 * 
 * Display the username, hostname and current working directory
 */
void prompt() {
    // get cwd, username and hostname
    char cwd[DEFUALT_BUFFER_SIZE];
    char *current_dir;
    char *username;
    char hostname[DEFUALT_BUFFER_SIZE];

    getcwd(cwd, sizeof(cwd));
    // get the current directory name
    current_dir = strrchr(cwd, '/');
    if (current_dir != NULL) {
        current_dir++; 
    } else {
        current_dir = cwd;
    }
    
    username = getlogin();

    gethostname(hostname, sizeof(hostname));
    // take the first part of the hostname
    char *dot = strchr(hostname, '.');
    if (dot != NULL) {
        *dot = '\0';
    }

    printf("(BASH_ir) %s@%s: %s$ ", username, hostname, current_dir);
}

/*
 * Main shell loop
 * Returns: exit code (0 for success, 1 for failure)
 */
int shellLoop() {
    
    // decide if the shell is running in interactive mode
    if (isInteractive()) {
        
        prompt();

        char *input;
        char **args;
        int status;

        input = getUserInput();
        args = parseInput(input);
        status = execute_args(args);

        // free memory
        free(input);
        free(args);
        
        // exit if status is not 0
        if (status > 0) {
            printf("Exiting.\n");
            return EXIT_FAILURE;
        }
    } 
    else {
        // TODO: implement non-interactive mode (scripting)
    }
    return 0;
}

/*
 * Signal handler for SIGINT
 * 
 * Allows the shell to catch SIGINT (Ctrl+C) and act accordingly
 */
void sigint_handler() {
    signal(SIGINT, sigint_handler);
    printf("\n");
    prompt();
    fflush(stdout);
}

int main() {

    // catch SIGINT signal
    signal(SIGINT, sigint_handler);

    int status = 0;
    while (status == 0) {
        status = shellLoop();
    }
    return status;
}