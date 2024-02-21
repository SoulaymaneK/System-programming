//
// Created by Soulaymane  on 09/12/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void zombie() {
    pid_t pid;

    // Création du processus enfant
    pid = fork();
    switch (pid) {
        case -1:
            // Erreur lors de la création du processus enfant
            fprintf(stderr, "Erreur lors de la création du processus enfant\n");
            exit(EXIT_FAILURE);
        case 0:
            printf("Processus enfant : Je suis ici et je vais dormir pendant 1 minute.\n");
            sleep(60); // Le processus enfant dort pendant 60 secondes
            printf("Processus enfant : Je me réveille maintenant.\n");
            exit(0);
        default:
            // Code exécuté par le processus parent
            printf("Processus parent : Le processus enfant a été créé avec le PID : %d\n", pid);
            // Attente de la fin du processus enfant
            waitpid(pid,NULL,0);
            printf("Processus parent : Le processus enfant s'est terminé.\n");
    }

}
