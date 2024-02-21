#include <stdio.h>
#define N 10 // Définit le nombre de notes
/*
 *
 * QUESTION 1
 *
 */
// Cette fonction récupère un tableau d'entier de taille N, et le remplit avec les notes rentrées par l'utilisateur
void note_sr01(int POINTS[N]){
    printf("Entrez la 1er note :");
    scanf("%d",POINTS);
    for (int i = 1; i < N; ++i) {
        printf("Entrez la %d-eme note :",i+1);
        scanf("%d",POINTS+i);
    }
    return;
}



/*
 *
 * QUESTION 2
 *
 */
//Permet de calculer la note maximale du tableau POINTS
int note_max(int tab[N]){
    int max =0; // le max est initialisé à la valeur minimale 0
    for (int i = 0; i < N; i++ ){
        if (tab[i] > max){ // Si la valeur est supérieure au max, elle devient le nouveau max
            max = tab[i];
        }
    }
    return max;
}
//Permet de calculer la note minimale du tableau POINTS
int note_min(int tab[N]){
    int min =60; // le min est initialisé à la valeur maximale 60
    for (int i = 0; i < N; i++ ){
        if (tab[i] < min){ // Si la valeur est inférieure au min, elle devient le nouveau min
            min = tab[i];
        }
    }
    return min;
}
//Permet de calculer la moyenne du tableau POINTS
float moyenne_note(int tab[N]){
    float moyenne, somme = 0;
    for (int i = 0; i < N; i++ ){ // Boucle for pour additionner toutes les valeurs de POINTS entre elles
        somme += tab[i];
    }
    moyenne = somme/N;
    return moyenne;
}

/*
 *
 * QUESTION 3
 *
 */
// Création du tableau NOTES à partir du tableau POINTS
void init_notes(int notes[7],int points[N]){
    for (int k = 0; k < 7; k++){ // Initialiser chaque valeur du tableau NOTES à 0 pour pouvoir les incrémenter plus tard
        notes[k] = 0;
    }
    for (int i = 0; i < N; i++){ // Incrémentation du tableau NOTES en fonction de l'intervalle de chaque note
        if(points[i] <= 9) notes[0]++;
        else if (points[i] <= 19) notes[1]++;
        else if (points[i] <= 29) notes[2]++;
        else if (points[i] <= 39) notes[3]++;
        else if (points[i] <= 49) notes[4]++;
        else if (points[i] <= 59) notes[5]++;
        else notes[6]++;
    }
}

/*
 *
 * QUESTION 4
 *
 */
// Détermine MAXN, le maximum du tableau NOTES afin de réaliser les graphiques
int max_notes(int tab[7]){
    int max =0;
    for (int i = 0; i < 7; i++ ){
        if (tab[i] > max){
            max = tab[i];
        }
    }
    return max;
}


void nuage(int notes[7]){
    int maxn = max_notes(notes);
    for (int i = maxn; i > 0 ; i--){
        printf("%d >",i);
        printf("\t");
        for(int j = 0; j <7; j++){
            printf("    ");
            if(notes[j] == i) printf("o");
            else printf(" ");
            printf("   ");
        }
        printf("\n");
    }
    printf("\t");
    for(int k = 0; k < 7; k++){
        printf("+---");
        if(notes[k] == 0) printf("o");
        else printf("-");
        printf("---");
    }
    printf("+");
    printf("\n");
    printf("\t");
    printf("  |0-9|\t|10-19|\t|20-29|\t|30-39|\t|40-49|\t|50-59|\t| 60 |\n");

}

/*
 *
 * QUESTION 5
 *
 */

void baton(int notes[7]){
    int maxn = max_notes(notes);
    for (int i = maxn; i > 0 ; i--){
        printf("%d >",i);
        printf("\t");
        printf(" ");
        for(int j = 0; j <7; j++){

            if(notes[j] >= i) printf("#######");
            else printf("       ");
            printf(" ");
        }
        printf("\n");
    }
    printf("\t");
    for(int k = 0; k < 7; k++){
        printf("+-------");
    }
    printf("+");
    printf("\n");
    printf("\t");
    printf("  |0-9|\t|10-19|\t|20-29|\t|30-39|\t|40-49|\t|50-59|\t| 60 |\n");

}


int main() {
    int points[N], notes[7];
    note_sr01(points);
    printf("La note maximale est : %d \n La note minimale est : %d \n La moyenne est : %f\n", note_max(points), note_min(points),
           moyenne_note(points));
    init_notes(notes,points);

    printf("\n");
    nuage(notes);
    printf("\n");
    baton(notes);
    return 0;
}