#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#define BUFFER_SIZE 128
#define MAX_ARGS 10

int main() {
    char buffer[BUFFER_SIZE];
    char *args[MAX_ARGS];
    char prompt_with_status[BUFFER_SIZE];
    const char *welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    pid_t pid;
    int status;
    write(STDOUT_FILENO, welcome_msg, strlen(welcome_msg));
    snprintf(prompt_with_status, BUFFER_SIZE, "enseash %% ");

    while (1) {
        write(STDOUT_FILENO, prompt_with_status, strlen(prompt_with_status));
        ssize_t len = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);

        if (len <= 0 || strcmp(buffer, "exit") == 0) { 
            write(STDOUT_FILENO, "Bye bye...\n", 11);
            break;
        }

        buffer[len - 1] = '\0';

        int arg_count = 0;
        char *input_file = NULL;
        char *output_file = NULL;
        char *token = strtok(buffer, " ");
        while (token != NULL && arg_count < MAX_ARGS - 1) {
            if (strcmp(token, "<") == 0) {
                token = strtok(NULL, " ");
                input_file = token; 
            } else if (strcmp(token, ">") == 0) {
                token = strtok(NULL, " ");
                 output_file = token; 
            } else {
                args[arg_count++] = token;
            }
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; 
pid = fork();
        if (pid == 0) {
            
            if (input_file != NULL) {
                int fd_in = open(input_file, O_RDONLY);
                if (fd_in == -1) {
                    perror("Error opening input file");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
if (output_file != NULL) {
                int fd_out = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd_out == -1) {
                    perror("Error opening output file");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }

            execvp(args[0], args);
            perror("Error executing command");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            wait(&status);
            if (WIFEXITED(status)) {
                snprintf(prompt_with_status, BUFFER_SIZE, "enseash [exit:%d] %% ", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                snprintf(prompt_with_status, BUFFER_SIZE, "enseash [sign:%d] %% ", WTERMSIG(status));
            }
        }
    }
    return 0;
}
