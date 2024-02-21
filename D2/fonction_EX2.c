//
// Created by Soulaymane  on 17/12/2023.
//
#include "prototype_fonction.h"
/*
 Dans cet exercice l’objectif est de faire communiquer un processus fils avec son processus père.
 Le processus fils doit écrire un entier dans un fichier, puis le processus père doit récupèrer cet
 entier en le lisant dans le fichier.
 */

int nb1, nb2;//variable globale

void ecrire_fils(int nb, char* name){
    FILE *file = fopen(name,"wb");
    if (file==NULL){
        perror("Erreur dans l'ouverture du fichier");
        exit(0);
    }
    fprintf(file,"%d",nb);
    fclose(file);
}

int lire_pere(int* nb, char* name) {
    FILE *file = fopen(name, "r");
    if (file == NULL) {
        perror("Erreur dans l'ouverture du fichier");
        exit(0);
    }
    if (fscanf(file, "%d", nb) != 1) {
        perror("Erreur dans la lecture du nombre par le père");
        fclose(file);
        return 0;
    }
    fclose(file);
    if (remove(name) != 0) {
        return 0;
    }
    return 1;
}

void handle_signal(int signum) {
    if (signum == SIGUSR1) {
        printf("Signal du premier fils reçu.\n");
        ecrire_fils(nb1,nom_fichiers(getppid(),'g'));
    } else if (signum == SIGUSR2) {
        printf("Signal du deuxième fils reçu.\n");
        ecrire_fils(nb2,nom_fichiers(getppid(),'d'));
    } else {
        printf("Signal inattendu reçu.\n");
        return;
    }
}
char* nom_fichiers(pid_t pid, char cote){//fonction qui génère un nom de fichier à partir d'un pid
    char* nom_fichier = malloc(15*sizeof(char));//crée une chaine de 15 caractères
    //Le nom du fichier contient l'id processus père plus g ou d si c'est le fils droit ou gauche
    sprintf(nom_fichier, "%d%c.txt", pid,cote);
    return nom_fichier;
}

int ex2_1() {
    printf("Entrez un nombre : ");
    scanf("%d",&nb1);

    int nb1_p;
    pid_t pid;
    pid = fork();

    switch (pid) {
        case -1:
            printf("erreur dans la création du processus");
            exit(EXIT_FAILURE);
        case 0:
            ecrire_fils(nb1, nom_fichiers(getppid(),'g'));
            exit(0);
        default:
            waitpid(pid,NULL,0);
            lire_pere(&nb1_p,nom_fichiers(getpid(),'g'));
            printf("Nombre récupéré par le père : \033[1m%d\033[0m\n",nb1_p);

    }
    return 0;
}


int ex2_2() {
    pid_t pid1, pid2;
    int nb1_p, nb2_p;
    printf("Entrez un premier nombre : ");
    scanf("%d",&nb1);
    printf("Entrez un second nombre : ");
    scanf("%d",&nb2);

    // Création du premier fils
    pid1 = fork();

    switch (pid1) {
        case -1:
            perror("Erreur dans la création du premier processus fils");
            exit(1);
        case 0:// Code du premier fils
            signal(SIGUSR1, handle_signal);// Attache le signal SIGUSR1 au gestionnaire de signaux
            pause(); // Attends jusqu'à la réception du signal
            exit(0);
        default:// Code du processus parent
            pid2 = fork();// Création du deuxième fils
            switch (pid2) {
                case -1:
                    perror("Erreur dans la création du deuxième processus fils");
                    exit(1);
                case 0:
                    signal(SIGUSR2, handle_signal); // Attache le signal SIGUSR2 au gestionnaire de signaux
                    pause(); // Attends jusqu'à la réception du signal
                    exit(0);
                default:// Code du processus parent
                    sleep(1); // Attente d'une seconde pour être sûr que les fils sont prêts

                    // Envoi des signaux aux fils pour qu'ils écrivent dans les fichiers
                    kill(pid1, SIGUSR1);
                    kill(pid2, SIGUSR2);

                    // Attente de la fin des fils
                    waitpid(pid1,NULL,0);
                    // Lecture des fichiers et récupération des valeurs
                    lire_pere(&nb1_p, nom_fichiers(getpid(),'g'));
                    waitpid(pid2,NULL,0);
                    lire_pere(&nb2_p, nom_fichiers(getpid(),'d'));

                    printf("Nombre récupéré par le père depuis le fichier %s : \033[1m%d\033[0m\n",nom_fichiers(getppid(),'g'), nb1_p);
                    printf("Nombre récupéré par le père depuis le fichier %s : \033[1m%d\033[0m\n",nom_fichiers(getppid(),'d'), nb2_p);
            }
            return 0;
    }
}

// Vider le buffer (utile quand on utilise des getchar() )
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}