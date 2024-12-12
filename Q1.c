# include <stdlib.h>
# include <stdio.h> 
# include <string.h>
# include <unistd.h>


# define message "Bienvenue dans la shell"

int mquestion1() 

{


write(STDOUT_FILENO, "Bienvenu dans la shelle de l'ensea \n",31);
write(STDOUT_FILENO, "Pour quitter taper exit\n",28);
        while(1) {

 
            write(STDOUT_FILENO, "enseash %",10);

            char command[128]; 
            
            ssize_t size = read(STDERR_FILENO, command, 128); 

            
            if (size <=0)
                            
                    {
                    break;                       
                     }

            command[size-1] = '\0';
                
            if (strcmp(command, "exit")==0)
            {
                write(STDOUT_FILENO, "Bye,Bye... \n", 11);
                break;
            }

             write(STDOUT_FILENO,"command inconnue. \n",20); 

        }
    
}
