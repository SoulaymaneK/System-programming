//
// Created by Soulaymane  on 15/10/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define L_MAX 1000//nombres max des restaurants dans le fichier
#define N_MAX 100//nombre de caractère max pour une chaine de caractère

//Structure pour définir la position de chaque restaurant
typedef struct Position{
    double x;
    double y;
}Position;

typedef Position *T_position;

//structure pour stocker dans un restaurant son nom, son adresse, sa position, et sa ou ses spécialités.
typedef struct Restaurant{
    char *nom_restaurant;
    char *adresse_restaurant;
    T_position position_restaurant;
    char *specialite;
}Restaurant;

// Structure pour stocker un restaurant et sa distance par rapport à la position actuelle.
typedef struct RestaurantDistance{
    Restaurant restaurant;
    double distance;
} RestaurantDistance;


int lire_restaurant(char* chemin, Restaurant restaurant[]);
//permet de lire les restaurants d'un fichier
int inserer_restaurant(Restaurant r);
//permet d'inserer en fin de fichier un restaurant
int cherche_restaurant(double x, double y, double rayon_recherche, Restaurant results[]);
//permet de chercher un restaurant dans un rayon de recherche, la fonction stockera selon la distance tous les restaurants dans le rayon dans le tableau results
// et affichera à l'écran les restaurants et leur distance de l'utilisateur
void cherche_par_specialite(double x, double y, char *specialite[], Restaurant results[]);
//permet de chercher un restaurant selon une ou des spécialités, la fonction stockera selon les spécialités tous les restaurants qui en satisfont au moins une
// dans le tableau results et affichera à l'écran les restaurants et leur distance de l'utilisateur
double calc_distance(Position *pos1, double x, double y);
//permet de calculer la distance entre la position d'un restaurant et les coordoonées d'un utilisateur
void viderBuffer();
// Vider le buffer (utile quand on utilise des getchar())