#include <stdio.h>
/*
 *  QUESTION 1
 */
int q1(){
    int A=20 , B =5;
    //int C= !--A/++!B;
    //printf (" A=%d B=%d c=%d \n", A,B, C);
}
/*
  Résultat : Ne fonctionne pas

    Explication :

    L'opérateur ! (not) renvoie un booléen 0 ou 1. Cependant, l'opération ++ tente d'incrémenter un booléen ce qui est impossible.
    Voilà pourquoi il n'est pas possible de compiler ce programme.
 */

/*
 *  QUESTION 2
 */

int q2(){
    int A=20 , B=5 , C= -10 , D =2;
    printf ("%d \n",  A && B || !0 && C++ && !D++) ;
    printf ("c=%d d=%d \n", C, D);
}
/*
  Résultat : 1
             c=-10 d=2

    Explication :
    A && B -> donne 1 car A et B sont différents de 0 (&& prioritaire)
    Ensuite, il y a un OU logique entre (A && B) et (!0 && C++ && !D++)
    Cependant, (A && B) = 1 donc il n'y a pas besoin de calculer la partie de droite du OU logique
    car le OU est forcément égal à 1 si l'une des deux parties est égale à 1.

    C'est pour cela que les valeurs des variables C et D ne changent pas.
 */

/*
 *  QUESTION 3
 */

int q3(){
    int p [4]={1 , -2 ,3 ,4};
    int *q = p;

    printf (" c=%d \n", *++q * *q++) ;
    printf (" c=%d \n" ,*q);
}

/*
  Résultat :  c=4
              c=3

  Explication :

  on définit un pointeur q = p ; Ainsi q pointe vers la première valeur du tableau p, c'est à dire 1

  Ensuite pour ( *++q * *q++ )
  *++q : q est incrémenté, q étant une adresse, q désigne l'adresse de la deuxieme valeur du tableau p
  l'étoile indique la valeur pointée par q c'est à dire -2

  Pour *q++, *q pointe donc vers -2, puis à la fin de l'opération l'adresse q sera incrémentée de 1 et pointera vers 3.

  On a donc une multiplication de -2 par -2 donnant 4

  Puis comme expliqué, à la fin de l'opération q pointe vers 3 donc *p = 3
 */


/*
 *  QUESTION 4
 */

int q4(){
    int p [4]={1 , -2 ,3 ,4};
    int *q = p;
    int d= *q & *q++ | *q++;

    printf (" d=%d \n", d);

    printf (" q=%d \n" ,*q);
}


/*
  Résultat :  d=-1
              q=3

 p et q sont définis de manière similaire à l'exercice précédent

 d = *q & *q++ | *q++

 priorité sur le & par rapport au |

 *q pointe vers 1 donc  *q & *q++ = 1 et l'adresse q sera incrémenté pour l'opération suivante
 on a 1 | *q++
 q pointe désormais vers -2, q sera incrémenté après l'opération
 on a donc 1 | -2

 2 en binaire : 000....010 -> complément à 2 : 111....101 -> +1 : 111....110

 000....001 | 111....110 = 111....111 -> complément à 2 : 000....000 -> +1 : 000....001 = 1

 on a ainsi d = -1 et q pointe  vers 3 donc q* = 3


 */


/*
 *  QUESTION 5
 */

int q5(){
    int a=-8 , b =3;
    int c = ++a && --b ? b-- : a++;
    printf (" a=%d b=%d c=%d \n",a,b, c);
}

/*
  Résultat :  a=-7 b=1 c=2

  ++a && --b ? b-- : a++

  ++a -> a = -7 préfixe donc se fait avant le &&
  --b -> b = 2

  -7 && 2 = 1 car -7 et 2 sont différents de 0

  comme ++a && --b = 1, b-- est réalisé.
  donc c = 2, puis b est décrementé, b = 1

  On a ainsi a = -7 ; b = 1 et c = 2


 */

/*
 *  QUESTION 6
 */

int q6(){
    int a=-8 , b =3;
    a>>= 2^b;
    printf ("a=%d \n",a);
}


/*
  Résultat :  a=-4

  a>>= 2^b

  l'opération en priorité est 2^b avec ^ représentant le XOR
  on a donc 2 XOR 3

  010 ^ 011 = 1

  on a donc a >>= 1
  ce qui correspond à un décalage à droite de 1 bit

  8 en binaire : 000....1000 -> complément à 2  : 111....0111 -> +1 : 111....1000
  décalage de 1 bit à droite : 111....100 -> complément à 2 : 000....011 -> +1 : 000....100 = 4
  donc a = -4
 */

int main() {
    //q1();
    //q2();
    //q3();
    //q4();
    //q5();
    //q6();
    return 0;
}
