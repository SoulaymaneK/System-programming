//
// Created by Soulaymane  on 14/12/2023.
//
#include "fonction_EX3.c"
#include "zombie.c"

int main(){
    char choix = '_';
    while (choix != '0') {
        printf("\n===========DEVOIR 2 SR01===========\n");
        printf("1.Exercice 1 : fichier zombie.c\n");
        printf("2.Exercice 2 : sans les signaux\n");
        printf("3.Exercice 2 : avec les signaux\n");
        printf("4.Exercice 3 : division de tâches\n");
        printf("0.Quitter");
        printf("\n===================================\n");
        printf("Choisissez un nombre : ");
        choix = (char)getchar();
        viderBuffer();
        // supprimer de l'entrée standard le retour charriot et les éventuels caractères supplémentaires tapés par l'utilisateur
        switch (choix) {
            case '1':
                printf("\n===========EX1 - zombie.c===========\n");
                zombie();
                break;
            case '2':
                printf("\n===========EX2 - SANS les signaux===========\n");
                ex2_1();
                viderBuffer();
                break;
            case '3':
                printf("\n===========EX2 - AVEC les signaux===========\n");
                ex2_2();
                viderBuffer();
                break;
            case '4':
                printf("\n===========EX3 - division de tâches===========\n");
                ex3();
                break;
            case '0' :
                printf("\n==========Programme terminé==========\n");
                break;
            default:
                printf("\n\nErreur : votre choix n'est pas valide !");
        }
        printf("\n\n\n");

    }
}
