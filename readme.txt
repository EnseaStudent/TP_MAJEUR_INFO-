Avant porpos : 

  Pour chaque partie j'ai repris et enrichis dans la mesure du possible le code précédent directemet dans mon main.c 
  D'autre part la machine virtuelle ne reconnaissait pas les fonctions issues de le bibliothèque time

Code 1 - 

  Explications : 

Le code se contente d'attendre un "exit" en comparant l'entrée de l'utilisateur qu'il stocke dans un tableau de 128 entrées 
("command") à l'aide de la fonction "strcmp" en supprimant la dernier caratère de l'entrée de l'utilisateur s'agissant du '\n'

  Intér^t pédagogique :

Première approche des fonctions read, write et strcmp, l'idée de stocker l'entrée utilisateur dans un tableau n'était pas totalemnt intuitive. 

Code 2 - 

  Explications : 

Appel de la fonction fork() pour qui créé un processus enfant avec gestion d'erreur (si le processus n'exite pas entre autre)
Si pid == 0, le code s'exécute dans le processus enfant.
Si pid > 0, le code s'exécute dans le processus parent.
Si pid < 0, cela signifie que la création du processus a échoué.
Le processus enfant utilise execlp pour remplacer son image mémoire avec celle de la commande saisie par l'utilisateur (contenue dans command).
Puis gestion d'erreur en cas d'échec

La fonction execlp n'était pas evidente à utiliser 



  Intérêt pédagogique :

Usage de la fonction fork() et execlp et instanciation de processus 



Code 3- 

  Explications : 

Meme code que précedemment avec l'ajout de la gestion de l'entrée "CTRL + D"
il semble que j'ai mis cette fonctionnalité dans le code de la question 4. 
"""
if (len <= 0 || strcmp(buffer, "exit") == 0) { 
            write(STDOUT_FILENO, "Bye bye...\n", 11);
"""
                                                                                     

  Intérêt pédagogique :

usage de conditions logiques "||" ? 

                                                                                     

Code 4- 

  Explications : 

Usage de sprintf car seul printf est interdit (dit lors de la séance de tp ;) )
WIFEXITED : Vérifie si le processus enfant s'est terminé normalement. Affiche le code de sortie (exit:x) 
WIFSIGNALED : Vérifie si le processus enfant a été arrêté par un signal. Affiche le signal reçu (sign:x)
Mon code ne fonctionnait pas à la fin de la première séance en raison d'un mauvais usage des fonctions wifexited et wifsignaled 
                                                                                     
  Intérêt pédagogique

Usgae des fonctions Wifexited et wifsignaled







Code 5- 

  Explications : 

J'ai légèrement changer la structure des codes précédents pour plus de lisibilité avce plus de variavles constantes
Certaines fonctionnalité de la biblothèque time.h ne sont probablment pas compatibles avec notre machine virtuel
par exemple la fonctionnalité "CLOCK_MONOTONIC" n'est pas reconnue...

clock_gettime(CLOCK_MONOTONIC, &end et &start);  nous donnent en théorie les deux instants d'appel et de fin d'éxecution 
de nos processus. ce qui permet de calculer la durée d'éxecution que l'on peut ajouter toujours en théorie dans un write

                                                                                     
  Intérêt pédagogique :

USAGE de la bibliothèque time.h 




Code 6- 

  Explications : 

tokenisation
strtok : Divise la commande et ses arguments en tokens (chaînes séparées par des espaces)
                                                                                     
  Intérêt pédagogique :





Code 7- 

  Explications : 

comme les fonctionnalités liées au temps d'éxecution ne fonctionnent pas j'ai supprimé les lignes de code associées pour simplifier mon code
on reprend le système de tokenisation, on associe un token à notre variable fichier
pui gestion conditionnel de l'apport de fihier --> fonctions 'open', 'close' et 'dup2'
et gestion d'errur
                                                                                     
  Intérêt pédagogique :

appréhensions des nouvelles fonctions open close et dup2 (traitement d'un fichier à bas niveau ?) 



