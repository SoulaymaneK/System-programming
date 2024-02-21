//
// Created by Soulaymane  on 15/12/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "sys/wait.h"


void ecrire_fils(int nb, char* name);//ecrire un entier dans un fichier
int lire_pere(int* nb, char* name);//lire un entier contenu dans un fichier
void handle_signal(int signum);//fonction réalisé lors de la reception d'un signal signum
char* nom_fichiers(pid_t pid, char cote);//génére un nom de fichier
int maxi(int i, int j);//max entre 2 entiers
int max(int* tab, int debut, int fin);//max séquentiel dans un tab
int parallel_max(int* tab, int debut, int fin);//max recherché parallèlement par la division de tâche
void viderBuffer();//vide le buffer d'entré






