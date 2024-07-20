#include "fonction.h"

void print_current_state(MT mt, BD in) {
    BD temp = in;
    int pos = 0;

    // Trouver la position de la tête de lecture
    while (temp->left) {
        temp = temp->left;
        pos++;
    }

    printf("Bande : ");
    temp = in;

    // Afficher la bande avec l'indice en rouge
    while (temp) {
        if (temp == in) {
            printf("\033[31m%c\033[0m", temp->ltr); // Afficher en rouge
        } else {
            printf("%c", temp->ltr);
        }
        temp = temp->right;
    }
    printf("\n");

    printf("Etat actuel [%s] , Input [%c] -> Etat final [%s] , Valeur remplacée [%c], Déplacement : %s\n\n",
           mt->act, in->ltr, mt->act, in->ltr,
           mt->t->d == RIGHT ? "RIGHT" : (mt->t->d == LEFT ? "LEFT" : "STAY"));
}

BD init_BD(BD bd){
     bd = malloc(sizeof(struct bande));
     bd->left = NULL;
     bd->right = NULL;
     return bd;
}


BD create_BD(char *input){
     BD bd = NULL;
     bd = init_BD(bd);
     bd->left = NULL;
     BD prev = NULL;
     BD head = bd;
     int i = 0;
     int size = strlen(input);

     while(i <= size ){ // Evité les While(1) au maximum
          bd->ltr = input[i];
          bd->right = init_BD(bd->right);
          prev = bd;
          bd = bd->right;  
          bd->left = prev;
          i++;
     }
     bd->right = NULL;

     return head;
}