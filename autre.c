#include "fonction.h"

/* L'idée est de gardé la MT sous la forme a,b,c,d mais de convertir l'input {1,0} sous la forme {a,b,c,d} pour ensuite appliqué la MT précédente */
//MT 4 ---> Somme(A+C) == PAIR


void create_txt(char *machinenum){  
     char *machine = name(machinenum);
     char *str = fill(machine);
     char loc[2048] = "";
     strcpy(loc,str);
     char *lstr = NULL;
     char init = 0; //Etat initial MT entrée
     char accept = 0; //Etat final MT sortie
     //Init
     strtok(str,":");
     lstr = strtok(NULL,"\n");
     init = lstr[0];
     
     //Accept
     strtok(NULL,":");
     lstr = strtok(NULL,"\n");
     accept = lstr[0]; 
     strcpy(loc,strtok(NULL,"/"));

     FILE *f = fopen("TuringMachine_abcd.txt","w");
     fprintf(f,"init:X\n");
     fprintf(f,"accepte:%c\n",accept);
     // on lit deux caractère on va dans l'état A apres avoir lu 00, ect... ( on supprime les 0,1 au fur et a mesure )
     fprintf(f,"X,1,Y,_,r\nY,1,D,_,r\nY,0,C,_,r\nX,0,Z,_,r\nZ,1,B,_,r\nZ,0,A,_,r\n"); 
     // on place la tête de lecture à la fin pour écrire la lettre
     fprintf(f,"D,0,D,0,r\nD,1,D,1,r\nD,a,D,a,r\nD,b,D,b,r\nD,c,D,c,r\nD,d,D,d,r\n");//Pour D
     fprintf(f,"C,0,C,0,r\nC,1,C,1,r\nC,a,C,a,r\nC,b,C,b,r\nC,c,C,c,r\nC,d,C,d,r\n");//Pour C
     fprintf(f,"B,0,B,0,r\nB,1,B,1,r\nB,a,B,a,r\nB,b,B,b,r\nB,c,B,c,r\nB,d,B,d,r\n");//Pour B
     fprintf(f,"A,0,A,0,r\nA,1,A,1,r\nA,a,A,a,r\nA,b,A,b,r\nA,c,A,c,r\nA,d,A,d,r\n");//Pour A

     //Ensuite on écrit la lettre à la fin de l'input
     fprintf(f,"A,_,I,a,l\nB,_,I,b,l\nC,_,I,c,l\nD,_,I,d,l\n");
     
     //On Replace la tête  de lecture a gauche
     fprintf(f,"I,0,I,0,l\nI,1,I,1,l\nI,a,I,a,l\nI,b,I,b,l\nI,c,I,c,l\nI,d,I,d,l\n");

     //On revient vers l'état initial est la première valeur
     fprintf(f,"I,_,X,_,r\n");

     //Si nombre de impair (111) {reject} -> on remplace tout les chiffres par des lettres
     //Quand on est sur X avec une lettres c'est que tout les chiffre sont transformé d'ou :
     fprintf(f,"X,a,%c,a,s\nX,b,%c,b,s\nX,c,%c,c,s\nX,d,%c,d,s\n",init,init,init,init);

     //On recopie le contenue de l'ancienne MT
     fprintf(f,loc);
     fprintf(f,"/");
     free(machine);
     free(str);

     fclose(f);
}
int in_mt(MT m,int x,Transition e){
     for(int i = 0 ;i < x; i++){
          if(e.d == m->t[i].d && strcmp(e.EI,m->t[i].EI) == 0 && e.LTR == m->t[i].LTR && strcmp(e.NewEI,m->t[i].NewEI) && e.NewLTR == m->t[i].NewLTR) return 0;
     }
     return 1;
}
/* Dans cette solution on reste sur l'alphabet {0,1} sur la bande 
     L'objectif est de remplacer les liaisons 
     P(a) -> Q par :
     P(0) -> P0 / P0(0) -> Q                                     */

void new_q7(){
     MT mt = create_MT("4");
     FILE *f = fopen("TuringMachineQ7.txt","w");
     fprintf(f,"init:%s\n",mt->act);
     fprintf(f,"accepte:%s\n",mt->acc);

     for(int i = 0; i < mt->nbt ; i++){     
               switch (mt->t[i].LTR){
               case 'a':{
                    if(in_mt(mt,i,mt->t[i])){ 
                         fprintf(f,"%s,0,%s0,0,r\n%s0,0,%s,0,r\n",mt->t[i].EI,mt->t[i].EI,mt->t[i].EI,mt->t[i].NewEI);
                         break;
                    }
               }
               case 'b':{
                    if(in_mt(mt,i,mt->t[i])){ 
                         fprintf(f,"%s,0,%s0,0,r\n%s0,0,%s,0,r\n",mt->t[i].EI,mt->t[i].EI,mt->t[i].EI,mt->t[i].NewEI);
                         break;
                    }
               }
               case 'c':{
                    if(in_mt(mt,i,mt->t[i])){ 
                         fprintf(f,"%s,1,%s1,1,r\n%s1,1,%s,1,r\n",mt->t[i].EI,mt->t[i].EI,mt->t[i].EI,mt->t[i].NewEI);                              
                         break;
                    }                         
               }
               case 'd':{
                    if(in_mt(mt,i,mt->t[i])){ 
                         fprintf(f,"%s,1,%s1,1,r\n%s1,1,%s,1,r\n",mt->t[i].EI,mt->t[i].EI,mt->t[i].EI,mt->t[i].NewEI);                              
                         break;
                    }
               }                    
               }
               if(strcmp(mt->t[i].NewEI,mt->acc)==0){ // Etat final
                    fprintf(f,"%s,_,%s,_,s/",mt->t[i].EI,mt->acc);
               }
          }

     
     fclose(f);
     free_MT(mt);

}
int delete_tr(MT m,char *t,int *idxx,int *idxy){

     for(int i = 0;i < m->nbt;i++){
          for(int j = 0;j < m->nbt;j++){
               if(strcmp(m->t[j].NewEI,t)== 0 && strcmp(m->t[i].EI,t)==0 && i!=j){
                    *idxx = i;
                    *idxy = j;
                    return 1;
               }
          }   
     }
     return 0;
}


void Q9(){
     MT m = create_MT("5");
     
     FILE *f = fopen("TuringMachineQ9.txt","w");
     fprintf(f,"init:%s\n",m->act);
     fprintf(f,"accepte:%s\n",m->acc);

     int idxx = 0;
     int idxy = 0;
     for(int i = 0; i < m->nbt;i++){
          if(m->t[i].d == STAY && strcmp(m->t[i].NewEI,m->acc) && m->t[i].LTR == m->t[i].NewLTR){
               if(delete_tr(m,m->t[i].NewEI,&idxx,&idxy)){
                    printf("idxx = %d and idxy = %d i=%d NewEI :%s",idxx,idxy,i,m->t[i].NewEI);
                    m->t[idxx].use = 5;
                    m->t[idxy].use = 5;
                    fprintf(f,"%s,%c,%s,%c,%c\n",m->t[idxy].EI,m->t[idxx].LTR,m->t[idxx].NewEI,m->t[idxx].LTR,dir(m->t[idxy].d));
               }
          }
     }
     for(int i = 0;i < m->nbt;i++){
          if(strcmp(m->t[i].NewEI,m->acc) == 0){
               fprintf(f,"%s,_,%s,_,s/\n",m->t[i].EI,m->t[i].NewEI);
          }
          else{
               if(m->t[i].use == 0){
                    fprintf(f,"%s,%c,%s,%c,%c\n",m->t[i].EI,m->t[i].LTR,m->t[i].NewEI,m->t[i].NewLTR,dir(m->t[i].d));
               }    
          }
          
          
     }
     fclose(f);
     free_MT(m);

}
char dir(Direction d){
     switch (d){
     case RIGHT:{
          return 'r';              
     }
     case LEFT:{
          return 'l';
     }
     case STAY:{
          return 's';
               }
     default: return 0;
     }

}


void code_mort(char *machinenum,char* idx){
     MT m = NULL;
     m = create_MT(machinenum);
     m->Head = create_BD(idx);
     calcul(m);
     char direc = '\0';
     FILE *f = fopen("MachineTuringCodeMort.txt","w");
     fprintf(f,"init:%s\n",m->t[0].EI);
     fprintf(f,"accepte:%s\n",m->acc);

     for(int i = 0; i < m->nbt;i++){
          if(strcmp(m->t[i].NewEI,m->acc)==0){
               fprintf(f,"%s,_,%s,_,s\n",m->t[i].EI,m->t[i].NewEI);
          }
          else
          {
               if(m->t[i].use == 1){
                    direc = dir(m->t[i].d);
                    fprintf(f,"%s,%c,%s,%c,%c\n",m->t[i].EI,m->t[i].LTR,m->t[i].NewEI,m->t[i].NewLTR,direc);
               }              
          }                  
     }
     fclose(f);
}



char *fill(char *name){

     char *str = calloc(2048,sizeof(char));
     printf("Name : %s",name);
     FILE *f = fopen(name,"r");
     if(!f){
        printf("Cannot open file TuringMachine.txt\n");
        exit(0);
     }
     char buf[20]= "";
     while((fgets(buf,20,f)) != NULL){
         strcat(str,buf); // On stock le contenue du texte dans str
     }
     fclose(f);
     return  str;
}

char *name(const char *machinenum){
     char *machine = calloc(25,sizeof(char));
     strcpy(machine,"TuringMachine");
     strcat(machine,machinenum);
     strcat(machine, ".txt");
     return machine;
}

void free_BD(BD b){
     BD node = b;
     while(node){
          BD next = node->right;
          free(node);
          node = next;
     }
}

void free_TR(Transition *t,int nbt){

     for(int i = 0;i < nbt;i++){
          free(t[i].EI);
          free(t[i].NewEI);
     }
     free(t);

}
int in_etats(char **etats, char *etattest){
    for(int i = 0; i<10; i++){
        if(strcmp(etats[i], etattest) == 0){return 1;}
    }
    return 0;
}

void createfrombi(){
    MT mt6 = create_MT("2");
    FILE *f = fopen("TuringMachineQ6.txt","w");
    char **etats = (char**)malloc(10*sizeof(char*));
    for(int i = 0 ; i<10; i++){
        etats[i] = (char *)malloc(10*sizeof(char));
        strcpy(etats[i],"");
    }
    int placement = 0;
    //En-tête
    fprintf(f,"init:%sN\naccepte:%sN\n",mt6->act,mt6->acc);
    //Init
    fprintf(f,"%sN,0,%sNRightslide0,N,r\n",mt6->act,mt6->act);
    fprintf(f,"%sN,1,%sNRightslide1,N,r\n",mt6->act,mt6->act);
    //Décalage initial sur la droite
    fprintf(f,"%sNRightslide0,0,%sNRightslide0,0,r\n",mt6->act,mt6->act);
    fprintf(f,"%sNRightslide0,1,%sNRightslide1,0,r\n",mt6->act,mt6->act);
    fprintf(f,"%sNRightslide1,0,%sNRightslide0,1,r\n",mt6->act,mt6->act);
    fprintf(f,"%sNRightslide1,1,%sNRightslide1,1,r\n",mt6->act,mt6->act);
    fprintf(f,"%sNRightslide0,_,%sNLeftslide,0,l\n",mt6->act,mt6->act);
    fprintf(f,"%sNRightslide1,_,%sNLeftslide,1,l\n",mt6->act,mt6->act);
    //Retour à gauche
    fprintf(f,"%sNLeftslide,0,%sNLeftslide,0,l\n",mt6->act,mt6->act);
    fprintf(f,"%sNLeftslide,1,%sNLeftslide,1,l\n",mt6->act,mt6->act);
    //Arrivée, on met la tête au début et on met l'état initial de la première MT
    fprintf(f,"%sNLeftslide,N,%s,N,r\n",mt6->act,mt6->act);

    for(int i = 0;i<mt6->nbt; i++){
        //Transition de la MT d'entrée
        char LTR = (mt6->t[i].LTR == ' ') ? '_' : mt6->t[i].LTR;
        char NewLTR = (mt6->t[i].NewLTR == ' ') ? '_' : mt6->t[i].NewLTR;
        char d = dir(mt6->t[i].d);

        fprintf(f,"%s,%c,%s,%c,%c\n",mt6->t[i].EI,LTR,mt6->t[i].NewEI,NewLTR,d);

        if(in_etats(etats, mt6->t[i].EI) == 0){
            //En cas d'atteinte du bumper "N"
            fprintf(f,"%s,N,%sRightslideN,N,r\n",mt6->t[i].EI,mt6->t[i].EI);
            //Après "Bump", on décale tout d'une case vers la droite
            fprintf(f,"%sRightslideN,0,%sRightslide0,_,r\n",mt6->t[i].EI,mt6->t[i].EI);
            fprintf(f,"%sRightslideN,1,%sRightslide1,_,r\n",mt6->t[i].EI,mt6->t[i].EI);
            fprintf(f,"%sRightslideN,_,%s,_,s\n",mt6->t[i].EI,mt6->t[i].EI);
            //Décalage vers la droite ("Right slide")
            fprintf(f,"%sRightslide0,0,%sRightslide0,0,r\n",mt6->t[i].EI,mt6->t[i].EI);
            fprintf(f,"%sRightslide0,1,%sRightslide1,0,r\n",mt6->t[i].EI,mt6->t[i].EI);
            fprintf(f,"%sRightslide1,0,%sRightslide0,1,r\n",mt6->t[i].EI,mt6->t[i].EI);
            fprintf(f,"%sRightslide1,1,%sRightslide1,1,r\n",mt6->t[i].EI,mt6->t[i].EI);
            fprintf(f,"%sRightslide0,_,%sLeftslide,0,l\n",mt6->t[i].EI,mt6->t[i].EI);
            fprintf(f,"%sRightslide1,_,%sLeftslide,1,l\n",mt6->t[i].EI,mt6->t[i].EI);
            //Bump vers la gauche jusqu'au _ à droite du N("Left slide")
            fprintf(f,"%sLeftslide,0,%sLeftslide,0,l\n",mt6->t[i].EI,mt6->t[i].EI);
            fprintf(f,"%sLeftslide,1,%sLeftslide,1,l\n",mt6->t[i].EI,mt6->t[i].EI);
            fprintf(f,"%sLeftslide,N,%sRightslideN,N,r\n",mt6->t[i].EI,mt6->t[i].EI);
            fprintf(f,"%sLeftslide,_,%s,_,s\n",mt6->t[i].EI,mt6->t[i].EI);
            //On enregistre l'état pour éviter un doublon
            strcpy(etats[placement],mt6->t[i].EI);
            placement++;
        }
    }
    //Suite de transitions pour enlever le N, à partir de l'état acceptant
    //Passage à l'état de décalage
    fprintf(f, "%s,0,%sRight,0,r\n",mt6->acc,mt6->acc);
    fprintf(f, "%s,1,%sRight,1,r\n",mt6->acc,mt6->acc);
    //Décalage jusqu'au caractère de fin
    fprintf(f, "%sRight,0,%sRight,0,r\n",mt6->acc,mt6->acc);
    fprintf(f, "%sRight,1,%sRight,1,r\n",mt6->acc,mt6->acc);
    //Arrivée à la fin
    fprintf(f, "%sRight,_,%sLeft,_,l\n",mt6->acc,mt6->acc);
    fprintf(f, "%sLeft,0,%sLeft0,_,l\n",mt6->acc,mt6->acc);
    fprintf(f, "%sLeft,1,%sLeft1,_,l\n",mt6->acc,mt6->acc);
    //Décalage jusqu'au N
    fprintf(f, "%sLeft0,0,%sLeft0,0,l\n",mt6->acc,mt6->acc);
    fprintf(f, "%sLeft0,1,%sLeft1,0,l\n",mt6->acc,mt6->acc);
    fprintf(f, "%sLeft1,0,%sLeft0,1,l\n",mt6->acc,mt6->acc);
    fprintf(f, "%sLeft1,1,%sLeft1,1,l\n",mt6->acc,mt6->acc);
    //Arrivée au N
    fprintf(f, "%sLeft0,N,%sN,0,s\n",mt6->acc,mt6->acc);
    fprintf(f, "%sLeft1,N,%sN,1,s\n",mt6->acc,mt6->acc);

    fclose(f);
    free_MT(mt6);
    for(int i = 0 ; i <10;i++){
        free(etats[i]);
    }
    free(etats);
}

void free_MT(MT m){
     free_BD(m->Head);
     free_TR(m->t,m->nbt);
     free(m->act);
     free(m->acc);
     free(m);
}