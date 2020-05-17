#include <stdio.h>
#include "fonctions.h"
#include <math.h>
#include <stdlib.h>

Alerte* Verification(Position pos, Alerte* alerte,int* taille_tab_alerte,int nmbdeformlocales)
{
    int i;
    for (i=0;i<(*taille_tab_alerte);i++)
    {
        if (pos==(alerte+i)->position)
        {
            printf("la position existe deja\n");
            return NULL;
        }
    }
    Alerte* newalerte;
    *taille_tab_alerte=*taille_tab_alerte+1;
    newalerte = realloc(alerte,sizeof(Alerte)*(*taille_tab_alerte));
    if(newalerte == NULL)
    {
       printf("un probleme est survenu lors de l'allocation de memoire\n");
       return NULL;
    }
    (newalerte+i)->position=pos;
    (newalerte+i)->nombre_deformations_locales = nmbdeformlocales;
    return newalerte;
}

Alerte* ChercheAlerte(Position* paquet,int taillepak){
   Alerte* alertes = NULL;
   int i = 0,k;
   int nmbdeformlocales;
   int premierealerte = 0;
   int premierepos;
   int taillealertes = 0;
   while(premierealerte == 0 || i!=taillepak){
      for(k=0;k<taillepak;k++){
         if(abs(paquet[i]-paquet[k])<=100){
            nmbdeformlocales = nmbdeformlocales + 1;
         }
      }

      if(nmbdeformlocales>=100){
         alertes = malloc(sizeof(Alerte));
         taillealertes = taillealertes + 1;
         alertes[0].position = paquet[i];
         alertes[0].nombre_deformations_locales = nmbdeformlocales;
         nmbdeformlocales = 0;
         premierepos = i+1;
         premierealerte = 1;
      }
      else{
         nmbdeformlocales=0;
         i++
      }
   }
   if(alertes == NULL){
      return alertes;
   }
   for(i=premierepos;i<taillepak;i++){
      for(k=0;k<taillepak;k++){
         if(abs(paquet[i]-paquet[k])<=100){
            nmbdeformlocales = nmbdeformlocales + 1;
         }
      }
      if(nmbdeformlocales>=100){
         verification(paquet[i],alertes,&taillealertes,nmbdeformlocales);
         nmbdeformlocales = 0;
      }
      else{
      nmbdeformlocales = 0;
      }

   }

   return alertes;
}

