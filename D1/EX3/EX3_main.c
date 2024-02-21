//
// Created by Soulaymane  on 15/10/2023.
//

#include "EX3.c"

int main(){
    char choix = ' ';
    while (choix != '0') {
        //affichage du menu
        printf("\n==========MENU==========\n");
        printf("1. Lire le fichier des restaurants.\n");
        printf("2. Insérer une restaurant dans le fichier.\n");
        printf("3. Chercher un restaurant selon un rayon de recherhcer\n");
        printf("4. Chercher un restaurant selon des spécialités\n");
        printf("0. Quitter\n");
        printf("=======================\n");
        printf("\n   Votre choix ? : ");

        choix = (char)getchar();//getchar() va permettre à l'utilisateur de saisir un caractère

        Restaurant *r;
        r = malloc(L_MAX * sizeof(Restaurant));//allocation dynamique pour les restaurants qu'on va utiliser
        Restaurant *r2;
        r2 = malloc(L_MAX * sizeof(Restaurant));
        Restaurant *r_inserer = malloc(sizeof(Restaurant));

        char chemin[N_MAX];//pour le chemin d'un fichier au cas où on veut adapter le programme avec un autre fichier

        double rayon,x,y;

        char *specialite[5];//on a fixé à 5 spécialité entrée par l'utilisateur pour la dernière question
        for (int i = 0; i < 5; i++) {
            specialite[i] = malloc(N_MAX * sizeof(char));//allocation dynamique pour chaque spécialité du tableau
        }

        switch (choix) {
            case '1':
                printf("\n==========Lecture fichier==========\n");
                printf("Entrez le chemin du fichier : \n");
                scanf(" %[^\n]", chemin);//permet de lire une chaine sans le '\n' qu'on peut avoir avec un fgets
                printf("%d restaurants lus à partir du fichier.\n", lire_restaurant(chemin,r));
                break;
            case '2':
                printf("\n==========Insertion Restaurant==========\n");
                if (strlen(chemin)>1) {
                    viderBuffer();
                    inserer_restaurant(*r_inserer);
                }
                else
                    printf("\nVeuillez commencer par lire le fichier des restaurants !\n");
                break;
            case '3':
                printf("\n==========Recherche Restaurant Selon Votre Poisition==========\n");
                printf("Entrez votre position : \n");
                printf("x = ");
                scanf("%lf",&x);
                printf("y = ");
                scanf("%lf",&y);
                printf("Entrez votre rayon de recherche : \n");
                printf("r = ");
                scanf("%lf",&rayon);
                printf("\n%d restaurants trouvés dans votre rayon\n",cherche_restaurant(x,y,rayon,r2));
                break;
            case '4':
                printf("\n==========Recherche Restaurant Selon des spécialités==========\n");
                printf("Entrez votre position : \n");
                printf("x = ");
                scanf("%lf",&x);
                printf("y = ");
                scanf("%lf",&y);
                int i =-1,cpt=1;//i indice dans la boucle pour traverser les cases du tableau sépcialité, cpt juste pour demander à l'utilisateur s'il veut continuer
                char c = '_';
                do {
                    i++;
                    printf("Entrez une spécialité : ");
                    scanf(" %[^\n]", specialite[i]);
                    viderBuffer();
                    printf("\nVoulez vous entrer une autre spécialité (o/n) : ");
                    scanf("%c",&c);
                    if (c=='o' || c=='O')
                        cpt = 1;
                    else
                        cpt = 0;
                } while (cpt==1);
                if (strlen(specialite[0])>0){//teste si l'utilisateur a ua moins entré une spécialité
                    cherche_par_specialite(x,y,specialite,r2);
                } else
                    printf("\nAucune spécilité entrée !\n");
                break;
            case '0':
                printf("\n=====Programme terminé=====\n");
                //on libère toute la mémoire alloué dynamiquement
                free(r);
                free(r2);
                free(r_inserer);
                for (int k = 0; k < 5; k++) {
                    free(specialite[k]);
                }
                break;
            default :
                printf("\n\nErreur : votre choix n'est pas valide !\n");
                break;
        }
        printf("\n\n");
        viderBuffer();
    }
}