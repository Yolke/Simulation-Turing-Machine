/*
 * ----------------------------------------------------------------------
 * Programme : Simulation d'une Machine de Turing
 * Auteur    : Jérémy Gago
 * Date      : 2021
 * Projet    : Université de Saint-Quentin
 * Description : Ce programme simule le fonctionnement d'une Machine de Turing
 *               à partir d'un fichier de configuration. Le fichier spécifie
 *               les états initiaux, les états d'acceptation et les transitions
 *               de la machine. La simulation lit l'entrée, applique les transitions
 *               en fonction de l'état courant et de la lettre lue, et déplace
 *               la tête de lecture sur la bande en conséquence. Le programme
 *               vérifie également le format du fichier de configuration pour
 *               s'assurer qu'il respecte les spécifications requises pour
 *               une Machine de Turing.
 * ----------------------------------------------------------------------
 * Use Case : 
 * 1. Préparer un fichier de configuration pour la Machine de Turing. 
 *    Le fichier doit contenir :
 *    - La ligne d'initialisation (format : "init:État_initial").
 *    - La ligne d'acceptation (format : "accepte:État_final").
 *    - Les transitions sous la forme "État_initial,Lettre_entrée,État_final,Lettre_remplacée,Déplacement",
 *      séparées par des deux-points (":") et terminées par un slash ("/").
 * 
 * 2. Exécuter le programme en ligne de commande avec le fichier de configuration comme argument :
 *    ./simulation <nom_du_fichier>
 *    Exemple : ./turing 2
 *             Ensuite taper l'entrée ex : "1100101"
 * 
 * 
 * 3. Le programme affichera la sortie de la Machine de Turing après avoir appliqué les transitions.
 * 
 * Remarque : Assurez-vous que le fichier de configuration respecte le format attendu pour éviter des erreurs
 *            lors de la simulation.
 * ----------------------------------------------------------------------
 */



#include "fonction.h"

int main(int argc, char* argv[]){
     char idx[512] = "1101010010";

     MT mt;
     if(strcmp(argv[1],"1") == 0){
          for(int i = 1; i<argc; i++){
               mt = create_MT(argv[i]);
               mt->Head = create_BD(idx);
               printf("\n");
               BD bds = calcul(mt);
               if (bds == NULL){
                    continue;
               }    
               printf("Sortie: ");
          }
     }
     if(strcmp(argv[1],"2") == 0){
          for(int i = 1; i<argc; i++){
               char loc[512];
               printf("Indiqué votre input :\n");
               scanf("%s",&loc);
               mt = create_MT(argv[i]);
               mt->Head = create_BD(loc);
               printf("\n");
               BD bds = calcul(mt);
               if (bds == NULL){
                    continue;
               }    
               printf("Sortie: ");
          }
     }
     
     if(mt)free_MT(mt);
     
     return 0;
}