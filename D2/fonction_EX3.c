
#include "fonction_EX2.c"
#define SEUIL 3//seuil pour savoir si on fait en division de processeur ou si on fait une recherche séquentiel
#define N_MAX 1000//nombre max d'élément pour tableau

int maxi(int i, int j){
    return i>j ? i : j;//fonction qui retourne le max entre deux valeurs
}

//fonction qui retourne le max d'un tableau dans un intervalle précisé
int max(int* tab, int debut, int fin){
    if (debut>fin)
        return -1;
    if (debut==fin)
        return tab[debut];

    int max = 0;
    for (int i = debut; i <= fin; ++i) {
        max = maxi(tab[i],max);
    }
    return max;
}


int parallel_max(int arr[], int debut, int fin) {
    if (fin - debut +1<= SEUIL) {  // Si la taille de la partie du tableau est inférieure au seuil, recherche séquentielle
        return max(arr, debut, fin);
    }

    int mid = (debut + fin) / 2;

    int left_max, right_max;
    pid_t left_child, right_child;

    left_child = fork();  // Créer un processus fils pour la première moitié du tableau
    switch (left_child) {
        case -1:
            perror("erreur avec le fork");
            exit(EXIT_FAILURE);
        case 0:
            // Code pour le fils gauche
            left_max = parallel_max(arr, debut, mid);
            ecrire_fils(left_max, nom_fichiers(getppid(),'g' ));
            // Écrire le maximum dans le fichier
            exit(0);
        default:
            right_child = fork();  // Créer un processus fils pour la deuxième moitié du tableau
            switch (right_child) {
                case -1:
                    perror("erreur avec le deuxieme fork");
                    exit(EXIT_FAILURE);
                case 0:
                    // Code pour le fils droit
                    right_max = parallel_max(arr, mid + 1, fin);
                    ecrire_fils(right_max, nom_fichiers(getppid(),'d'));
                    // Écrire le maximum dans le fichier
                    exit(0);
                default:
                    // Code pour le parent
                    waitpid(left_child, NULL, 0);
                    lire_pere(&left_max, nom_fichiers(getpid(),'g'));// Lire le maximum écrit par le fils gauche
                    waitpid(right_child, NULL, 0);
                    lire_pere(&right_max, nom_fichiers(getpid(),'d'));  // Lire le maximum écrit par le fils droit
                    return maxi(left_max,right_max);
            }
    }
}


int ex3(){
    int tab[N_MAX];
    for (int i = 0; i < N_MAX; ++i) {
        tab[i] = (int) rand();  // Remplir le tableau avec des nombres aléatoires entre 0 et 99
    }
    printf("Max trouver séquentiellement avec la fonction maxi : \033[1m%d\033[0m\n", max(tab,0,N_MAX-1));
    printf("Max trouver à l'aide de la division de tâche : \033[1m%d\033[0m\n",parallel_max(tab,0,N_MAX-1));
}



