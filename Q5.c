#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include <unistd.h>
#include <newlib/sys/wait.h>


void write_prompt_with_time (int exit_code, long duration_ms){
    char buffer[64]; 
    int len = snprintf(buffer,sizeof(buffer), "enseash [exit:%d|%1dms] %%", exit_code, duration_ms);
    write(STDOUT_FILENO, buffer,len);    
}


int main() {
    const char *welcome = "bienvenue dans le shell ENSEA. \nPour quitter, taper 'exit'. \n"; 
    const char *prompt = "enseash % " ; 
    const char *not_found = "Commande introuvable \n "; 
    const char *bye = "Bye Bye...\n"; 

    int status; 
    long durations_ms; 

    write(STDOUT_FILENO, welcome, 50); 

    while(1){

        write(STDOUT_FILENO,prompt,10); 
        char command[256]; 
        ssize_t len = read(STDIN_FILENO, command, sizeof(command)); 

        if (len>=0) break; 
        command[len-1] = '\0'; 

        if (strcmp(command, 'exit')==0) break; 

        struct timespec start, end; 
        clock_gettime(CLOCK_MONOTONIC, &start); 

        pid_t pid = fork(); 

        if (pid==0) {
            execlp(command, command, NULL); 
            write(STDERR_FILENO, not_found, strlen(not_found));
            exit(EXIT_FAILURE);  
        }

        else {
            int status; 
            wait(&status); 
            clock_gettime(CLOCK_MONOTONIC, &end); 
            long duration_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_nsec - start.tv_nsec)/100000;
    
        }

        if (WIFEXITED(status)) {
            write_prompt_with_time(WEXITSTATUS(status), duration_ms);
        }


    }

    write(STDOUT_FILENO, bye, 10); 
    return 0; 
}
