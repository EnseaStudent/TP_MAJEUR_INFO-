#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#define BUFFER_SIZE 128

int main() {
    char buffer[BUFFER_SIZE];
    char prompt_with_status[BUFFER_SIZE];
    const char *welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    pid_t pid;
    int status;
write(STDOUT_FILENO, welcome_msg, strlen(welcome_msg));
    snprintf(prompt_with_status, BUFFER_SIZE, "enseash %% ");
    while (1) {
        write(STDOUT_FILENO, prompt_with_status, strlen(prompt_with_status));
        ssize_t len = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        if (len <= 0 || strcmp(buffer, "exit") == 0) { // Gestion de exit ou ctrl+d
            write(STDOUT_FILENO, "Bye bye...\n", 11);
            break;
        }

        buffer[len - 1] = '\0'; // Remove newline
        pid = fork();
        if (pid == 0) {
            execlp(buffer, buffer, NULL);
            exit(EXIT_FAILURE); // Exit if command fails
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
