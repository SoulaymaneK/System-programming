//
// Created by Soulaymane  on 15/10/2023.
//

#include "EX3.h"

int lire_restaurant(char* chemin, Restaurant restaurant[]){
    FILE *file ;
    char ligne[L_MAX];
    int num_ligne = 0;

    file = fopen(chemin,"r");//en mode lecture
    if (file==NULL){
        printf("Impossible d'ouvrir le fichier ! \n");
        return 0;
    }

    while (fgets(ligne, sizeof(ligne), file) != NULL) {
        if (num_ligne==0)//pour sauter en quelque sort la première ligne du fichier qui contient les noms des colonnes
            num_ligne++;
        else if (strlen(ligne)>1) {//la condition permet de ne pas prendre en compte les lignes vides, comme les sauts de lignes etc...
            char *token = strtok(ligne, ";");//permet de récupérer chaque élément de la ligne entre chaque séparateur ";"
            int token_index = 0;//va nous permettre de compter à a quel élément de la ligne nous somme, exemple : 0 pour le nom, 1, pour l'adresse, etc...
            while (token != NULL && token_index<4) {
                switch (token_index) {
                    case 0:
                        restaurant[num_ligne - 1].nom_restaurant = malloc(strlen(token)+1); //on alloue dynamiquement pour ne pas restreindre la taille et ne pas trop prévoir
                        strcpy(restaurant[num_ligne - 1].nom_restaurant, token);//copier le nom du restaurant contenu dans token dans le restaurant[i].nom_restaurant
                        break;
                    case 1:
                        restaurant[num_ligne - 1].adresse_restaurant = malloc(strlen(token)+1);
                        strcpy(restaurant[num_ligne - 1].adresse_restaurant, token);
                        break;
                    case 2:
                        restaurant[num_ligne - 1].position_restaurant = malloc(sizeof(Position));
                        if (sscanf(strstr(token, "x="), "x=%lf", &restaurant[num_ligne - 1].position_restaurant->x) != 1) {
                            printf("Impossible d'extraire la valeur de x.\n");
                            return 0;
                        }
                        restaurant[num_ligne - 1].specialite = malloc(strlen(token)+1);
                        if (sscanf(strstr(token, "y="), "y=%lf", &restaurant[num_ligne - 1].position_restaurant->y) != 1) {
                            printf("Impossible d'extraire la valeur de y.\n");
                            return 0;
                        }
                        /* ces lignes de code recherche la sous-chaîne "x=" et "y=" dans le token (donc dans la partie des coordonnées),
                         * extrait un nombre décimal en virgule flottante qui suit cette sous-chaîne,
                         * puis stocke cette valeur dans les variable x et y du membre position_restaurant du restaurant
                         */
                        break;
                    case 3:
                        strcpy(restaurant[num_ligne - 1].specialite, token);
                        break;
                }
                token = strtok(NULL, ";");//permet de passer à l'élément suivant dans le découpage de la ligne
                token_index++;
            }
            num_ligne++;//compter les lignes
        }
    }
    fclose(file);//fermeture du fichier
    return num_ligne-1;//on return -1 car au début on à fait +1 pour passer la première ligne
}

int inserer_restaurant(Restaurant r){

    FILE *file;
    file = fopen("restau.txt","a");//ouverture en écriture pour des ajouts en fin de fichier
    if (file==NULL){
        printf("Impossible d'ouvrir le fichier ! \n");
        return 0;
    }

    printf("\nEntrez les informations du restaurant : \n");

    printf("- Nom du restaurant : ");
    r.nom_restaurant = malloc(sizeof(char*));
    fgets(r.nom_restaurant,100,stdin);
    r.nom_restaurant[strcspn(r.nom_restaurant, "\n")] = '\0'; //Sert à supprimer le '\n' qui se rajoute avec un fgets

    printf("- Adresse du restaurant : ");
    r.adresse_restaurant = malloc(sizeof(char*));
    fgets(r.adresse_restaurant,100,stdin);
    r.adresse_restaurant[strcspn(r.adresse_restaurant, "\n")] = '\0'; //Sert à supprimer le '\n' qui se rajoute avec un fgets

    printf("- Specialité du restaurant : ");
    r.specialite = malloc(sizeof(char*));
    fgets(r.specialite,100,stdin);
    r.specialite[strcspn(r.specialite, "\n")] = '\0'; //Sert à supprimer le '\n' qui se rajoute avec un fgets

    r.position_restaurant = malloc(sizeof(T_position));
    printf("- Position du restaurant : \n");
    printf("x = ");
    scanf("%lf",&r.position_restaurant->x);
    printf("y = ");
    scanf("%lf",&r.position_restaurant->y);

    fprintf(file,"\n%s; %s;(x=%lf,y=%lf); {%s};\n",r.nom_restaurant,r.adresse_restaurant,r.position_restaurant->x,r.position_restaurant->y,r.specialite);
    //on ecrit dans le fichier au même format que le reste des restaurants
    fclose(file);

    //on libére la mémoire précédemment allouée
    free(r.nom_restaurant);
    free(r.adresse_restaurant);
    free(r.specialite);
    free(r.position_restaurant);

    printf("\nLe restaurant a bien été inséré dans le fichier.\n");

    return 1;
}

//calculer la distance entre une position et 1 point donné
double calc_distance(Position *pos1, double x, double y) {
    double dx = pos1->x - x;
    double dy = pos1->y - y;
    return sqrt(pow(dx,2) + pow(dy,2));
}

int cherche_restaurant(double x, double y, double rayon_recherche, Restaurant results[]){

    Restaurant *allRestaurants;
    allRestaurants = malloc(L_MAX * sizeof(Restaurant));

    int numRestaurants = lire_restaurant("restau.txt", allRestaurants);//on relève le nombre de restaurant présent dans le fichier

    int nombre_result = 0;

    /*création d'un tableau pour stocker tous les restaurants et leur distance
     *chaque "case" du tableau comprendra un élément de type RestaurantDistance,
     *on pourra comme ça stocker dans une seule case du tableau un restaurant et sa distance avec l'usager*/
    RestaurantDistance *restaurantDistances = malloc(numRestaurants * sizeof(RestaurantDistance));

    // Calculez la distance pour chaque restaurant par rapport à la position actuelle de l'utilisateu
    // et stockez ces informations dans le tableau de RestaurantDistance.
    for (int i = 0; i < numRestaurants; i++) {
        double distance = calc_distance(allRestaurants[i].position_restaurant, x, y);
        restaurantDistances[i].restaurant = allRestaurants[i];
        restaurantDistances[i].distance = distance;
    }

    // Triez le tableau de RestaurantDistance en fonction de la distance (on effectue ici un tri par insertion).
    for (int i = 1; i < numRestaurants; i++) {
        RestaurantDistance temp = restaurantDistances[i];
        int j = i - 1;
        while (j >= 0 && restaurantDistances[j].distance > temp.distance) {
            restaurantDistances[j + 1] = restaurantDistances[j];
            j--;
        }
        restaurantDistances[j + 1] = temp;
    }

    //ici on affecte enfin les restaurantsé étant dans le rayon dans le tableau result passé en paramètre
    for (int i = 0; i < numRestaurants; ++i) {
        if (restaurantDistances[i].distance<=rayon_recherche){
            results[nombre_result] = restaurantDistances[i].restaurant;
            nombre_result++;//pour connaitre le nombre de restaurant dans le rayon
        }
    }

    if (nombre_result>0) {
        for (int i = 0; i < nombre_result; ++i) {
            printf("\n%s - Distance : %lf", results[i].nom_restaurant,calc_distance(results[i].position_restaurant,x,y));        }
    }//on afficher tous les restaux trouvés avec leur distance par rappor tà l'utilisateur
    printf("\n");
    return nombre_result;
}



void cherche_par_specialite(double x, double y, char *specialite[], Restaurant results[]) {

    Restaurant *allRestaurants;
    allRestaurants = malloc(L_MAX * sizeof(Restaurant));
    int numRestaurants = lire_restaurant("restau.txt", allRestaurants);//on relève le nombre de restaurant présent dans le fichier

    int nombre_result = 0;

    /*création d'un tableau pour stocker tous les restaurants et leur distance
    *chaque "case" du tableau comprendra un élément de type RestaurantDistance,
    *on pourra comme ça stocker dans une seule case du tableau un restaurant et sa distance avec l'usager*/
    RestaurantDistance *restaurantDistances = malloc(numRestaurants * sizeof(RestaurantDistance));

    // Calculez la distance pour chaque restaurant par rapport à la position actuelle de l'utilisateur
    // et stockez ces informations dans le tableau de RestaurantDistance.
    for (int i = 0; i < numRestaurants; i++) {
        double distance = calc_distance(allRestaurants[i].position_restaurant, x, y);
        restaurantDistances[i].restaurant = allRestaurants[i];
        restaurantDistances[i].distance = distance;
    }

    // Triez le tableau de RestaurantDistance en fonction de la distance (ici on effecture un tri par insertion).
    for (int i = 1; i < numRestaurants; i++) {
        RestaurantDistance temp = restaurantDistances[i];
        int j = i - 1;
        while (j >= 0 && restaurantDistances[j].distance > temp.distance) {
            restaurantDistances[j + 1] = restaurantDistances[j];
            j--;
        }
        restaurantDistances[j + 1] = temp;
    }

    // Parcourez le tableau trié et ajoutez les restaurants correspondant aux spécialités passées en paramètre
    for (int i = 0; i < numRestaurants; i++) {
        char *token = strtok(restaurantDistances[i].restaurant.specialite, "{ , }");
        //va permettre de séparer les diférentes spécialités du restaurant des séparateurs  "{ , }" pour bien isolé chaque sépcialitée

        while (token != NULL) {//boucle while parcourir toutes les spécialités du restaurant
            // Convertir la spécialité en minuscules pour la comparaison insensible à la casse
            for (int k = 0; token[k] != '\0'; k++) {
                token[k] = tolower(token[k]);//tolower va permettre de convertir en minuscule
            }
            for (int j = 0; specialite[j] != NULL; j++) {//boucle pour parcourir toutes spécialités entrées par l'utilisateur
                // Convertir la spécialité recherchée en minuscules pour la comparaison insensible à la casse
                char specialiteLower[N_MAX];
                strcpy(specialiteLower, specialite[j]);
                for (int k = 0; specialiteLower[k] != '\0'; k++) {
                    specialiteLower[k] = tolower(specialiteLower[k]);
                }
                //comparer les 2 spécialités en minuscule
                if (strcmp(token, specialiteLower) == 0) {
                    results[nombre_result] = restaurantDistances[i].restaurant;
                    nombre_result++;
                    break;
                }
            }

            token = strtok(NULL, ", ");//passer à la spécialité suivante du restaurant
        }
    }

    if(nombre_result>0){
        for (int i = 0; i < nombre_result; ++i) {
            printf("\n%s - Distance : %lf", results[i].nom_restaurant,results[i].position_restaurant->x,results[i].position_restaurant->y,
                   calc_distance(results[i].position_restaurant,x,y));
        }
        printf("\n\n%d restaurant(s) trouvé selon vos/votre spécialite(s)\n",nombre_result);
        //on affiche le nombre de restaurant trouvé et les différents restaurant du plus proche au plus loin
    } else
        printf("Aucun restaurant ne fait cette/ces spécialités !\n");


    // Libérer la mémoire allouée pour chaque spécialité
    for (int i = 0; i < numRestaurants; i++) {
        free(restaurantDistances[i].restaurant.specialite);
    }
    free(allRestaurants);
    free(restaurantDistances);
}

//permet de vider le buffer d'entré (utile pour getchar(c))
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}








