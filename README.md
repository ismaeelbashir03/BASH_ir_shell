# Custom Shell in C - BASH_ir

## Description
This project is a simple custom shell implemented in C.

## Features
- Basic command execution (e.g. ./executable arg1 arg2)
- Custom built-in commands (e.g., `cd`, `exit`, `ls`, `cat`, `echo`)

## Installation
To compile and run the custom shell, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/ismaeelbashir03/BASH_ir_shell.git
    ```
2. Navigate to the project directory:
    ```sh
    cd BASH_ir_SHELL
    ```
3. Compile the source code using make:
    ```sh
    make
    ```
4. Run the shell:
    ```sh
    ./output/BASH_ir
    ```

## Usage
Once the shell is running, you can use it to execute commands just like a regular shell. Here are some examples:

- Running a command:
    ```sh
    ls -l
    ```
- Using built-in commands:
    ```sh
    cd /path/to/directory
    ```
- Exiting the shell:
    ```sh
    exit
    ```
- Displaying the help message:
    ```sh
    help
    ```
- Running a script (sample script provided in the `sample_script` directory):
    ```sh
    ./sample_script/gof
    ```
    