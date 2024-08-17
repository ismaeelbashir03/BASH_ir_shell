#include "shell.h"

/*
 * Get user input from stdin
 * Returns: pointer to the input string
 */
char *getUserInput() {
    char *input = NULL;
    size_t bufsize = 0;

    // check if getline() fails
    if (getline(&input, &bufsize, stdin) == -1) {

        // check if EOF is reached
        if (feof(stdin)) {
            free(input);
            exit(EXIT_SUCCESS);
        }

        // otherwise, print error message and exit
        else
        {
            free(input); /* avoid memory leaks when getline fails */
            perror("error while reading the input from stdin");
            exit(EXIT_FAILURE);
        }
    }
    return (input);
}

/*
 * Parse user input
 * @input: string to be splited
 *
 * Return: pointer that points to the new array
 */
char **parseInput(char *input) {
    int bufsize = 64; // initial buffer size
    int i = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    // check if malloc fails
    if (!tokens) {
        fprintf(stderr, "allocation error in split_line: tokens\n");
        exit(EXIT_FAILURE);
    }

    // split the input string, by the delimiters
    token = strtok(input, TOK_DELIM);
    while (token != NULL) {
        
        // ignore comments
        if (token[0] == '#') {
            break;
        }

        tokens[i] = token;
        i++;

        // reallocate memory if buffer is full
        if (i >= bufsize) {
            bufsize += bufsize;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "reallocation error in split_line: tokens");
                exit(EXIT_FAILURE);
            }
        }

        // get the next token
        token = strtok(NULL, TOK_DELIM);
    }

    tokens[i] = NULL;
    return tokens;
}