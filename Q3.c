# include <stdlib.h>
# include <stdio.h> 
# include <string.h>
# include <unistd.h>
# include <time.h> 


int main() 

{


write(STDOUT_FILENO, "Bienvenu dans la shelle de l'ensea \n",31);
write(STDOUT_FILENO, "Pour quitter taper exit\n",28);
        while(1) {

 
            write(STDOUT_FILENO, "enseash %",10);

            char command[128]; 
            
            ssize_t size = read(STDERR_FILENO, command, 128); 

            if (size ==0)
                            
                    {
                    write(STDOUT_FILENO, "\nBye bye...\n", 12);      
                    break;                 
                     }
 
            if (size <0)
                            
                    {
                    perror("Erreur de lecture"); 
                    continue;                        
                     }

            command[size-1] = '\0';
                
            if (strcmp(command, "exit")==0)
            {
                write(STDOUT_FILENO, "Bye,Bye... \n", 11);
                break;
            }

            __pid_t pid = fork(); 
            if (pid == 0 )
            {
                execlp (command, command, NULL);

                perror("Erreur");
                exit(EXIT_FAILURE);
            }
            else if  (pid>0) {
                int status ; 
                wait(&status); 
            } else {

                perror("Erreur de création duprocesseus"); 
            }

        }

}
