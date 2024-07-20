#include "fonction.h"
#include <ctype.h>


MT init_MT(MT m){
     m = malloc(sizeof(struct mt));
     m->acc = NULL;
     m->act = NULL;

     m->nbt = 0;
     m->t = NULL;
     m->Head = NULL;
     return m;
}
Transition init_transi(Transition t){
     t.d = STAY;
     t.EI = NULL;
     t.LTR =  0;
     t.NewEI = NULL;
     t.NewLTR = 0;
     t.use = 0;
     return t;
}

MT create_MT(const char *machinenum){
     MT New = NULL;
     New = init_MT(New);
     char *machine = name(machinenum);
     char *str = fill(machine);
     int cpt = 0,k = 0;
     char *lstr = NULL;

     //Init
     strtok(str,":");
     lstr = strtok(NULL,"\n");
     New->act = malloc(strlen(lstr)+1);
     strcpy(New->act,lstr);
     if(!isalpha(New->act[strlen(lstr)-1])){
          New->act[strlen(lstr)-1] = '\0'; /// Pour ignorer lee "\n"
     }
     //Accept
     strtok(NULL,":");
     lstr = strtok(NULL,"\n");
     New->acc = malloc(strlen(lstr)+1);
     strcpy(New->acc,lstr); 
     if(!isalpha(New->acc[strlen(lstr)-1])){
          New->acc[strlen(lstr)-1] = '\0'; /// Pour ignorer lee "\n"
     }

     //printf("\nNew : %s\n",New->acc);
     //Transition
     while(1){
          if(cpt%5 != 4)lstr = strtok(NULL,","); 
          else {
               lstr = strtok(NULL,"\n");
          }
          if(!lstr)break;
          if(cpt%5 == 0){
               New->t = realloc(New->t,(k+1)*sizeof(Transition));
               New->t[k] = init_transi(New->t[k]);
               New->t[k].EI = malloc(strlen(lstr)+1);
               strcpy(New->t[k].EI,lstr);
          }
          if(cpt%5 == 1){
               if(lstr[0] == '_')New->t[k].LTR ='\0';
               else New->t[k].LTR = lstr[0];
          };
          if(cpt%5 == 2){
               New->t[k].NewEI = malloc(strlen(lstr)+1);
               strcpy(New->t[k].NewEI,lstr);
          }
          if(cpt%5 == 3){
               if(lstr[0] == '_')New->t[k].NewLTR ='\0';
               else New->t[k].NewLTR = lstr[0];
          }
          if(cpt%5 == 4){
               New->t[k].use = 0;
               if(lstr[0] == 'r')New->t[k].d = RIGHT;
               if(lstr[0] == 'l')New->t[k].d = LEFT;
               if(lstr[0] == 's')New->t[k].d = STAY;
               k++;
          }
          cpt++;
     }
     New->nbt = k;
     free(machine);
     free(str);

     return New;
}


BD calcul(MT mt){
     int verif = 0;
     BD in = mt->Head;
     while(strcmp(mt->act,mt->acc) != 0)
     {     
          for(int i = 0 ; i < mt->nbt ;i++){
               if((in->ltr == mt->t[i].LTR) && (strcmp(mt->t[i].EI,mt->act)==0)){
                    mt->t[i].use = 1;
                    if(strlen(mt->t[i].NewEI) != strlen(mt->act)){ 
                         free(mt->act);
                         mt->act = malloc((strlen(mt->t[i].NewEI)) * sizeof(char) + 1);
                         
                    }
                    strcpy(mt->act,mt->t[i].NewEI); 
                    in->ltr = mt->t[i].NewLTR;

                    print_current_state(mt->Head,in);

                    
               
                    if(mt->t[i].d == LEFT){  
                         printf("Déplacement : LEFT\n\n");
                         if(in->left)in = in->left;
                         else
                         {    printf("\n\nREALLOC LEFT !!! (ERREUR)\n\n");                            
                         }

                    }
                    else if(mt->t[i].d == RIGHT){
                         printf("Déplacement : RIGHT\n\n");
                         if(in->right)in = in->right;
                         else{
                              BD prev = in;
                              in->right = init_BD(in->right);
                              in = in->right;
                              in->left = prev;
                         }
                    }
                    else {printf("Déplacement : STAY\n\n");}

                    i = mt->nbt ;
                    verif = 1;
               }              
          }
          if(verif == 0){
               printf("Reject à l'état [%s] et au caractère [%c] \n\n",mt->act,in->ltr);
               return mt->Head;
          }
          verif = 0;
     }
     printf("Accept\n");
     return mt->Head;
}