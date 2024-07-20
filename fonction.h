#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/* Dans notre code on attend des transitions sous la forme A,1,B,0,>:
                                                  à la place de A,1
                                                                B,0,>
                                                  A = état début, 1 = imput , B = nouveau état ,0 = on remplace 1 -> 0 dans la bande , 'r' = droite
                                                  Même principe que sur TuringMachineSimulator
     On sépare les differentes transi avec des ":"
     Les états finaux ne sont accessible uniquement à la dernière transitions
*/

/* Structure de données */
typedef enum {
     RIGHT,LEFT,STAY
     }Direction;

typedef struct transition {
     char use;
     char *EI; // Etat initial
     char *NewEI; // New Etat initial
     char LTR; // lettre entrée
     char NewLTR; // lettre remplacer
     Direction d;
}Transition;

/* Représente la bande de la machine de turing */
typedef struct bande{ 
     struct bande *left;
     struct bande *right;
     char ltr;
}*BD;

/* Machine de Turing */
typedef struct mt{
     char *acc;//Accept
     char *act; //actuel
     Transition *t; // Stock les transition
     BD Head;
     int nbt; //NB de transition

}*MT;


/* Fonctions qui permettent de gérer la gestion de fichier TurinMachineX.txt */

//Remplace 1(machinenum) par TuringMachine1.txt (name)
char *name(const char *machinenum);
//Return le contenue du fichier TuringMachine.txt
char *fill(char *name);
void create_txt(char *machinenum);

/* Fonctions sur la structure BD */


//Affiche la bande
void print_current_state(MT mt, BD in);
//Initialise la bande
BD init_BD(BD bd);
//Fonction qui construit la bande, la fonction stock l'input en entrée
BD create_BD(char *input);


/* Fonctions sur la structure MT */

//Initialise la structure
MT init_MT(MT m);
//Fonction qui construit la MT à l'aide des fonctions précédente, on stockera toutes les informations du TXT dans la structure
MT create_MT(const char *machinenum);
//Fonction qui interprête la MT et l'input pour sortir une valeur de sortit
BD calcul(MT mt);


/* Fonction gestion mémoire */
void free_BD(BD b);
void free_MT(MT m);

/* Initialise structure Transition */
Transition init_transi(Transition t);

void new_q7();
void code_mort(char *machinenum,char* idx);
char dir(Direction d);
void Q9();
void createfrombi();
int in_etats(char **etats, char *etattest);