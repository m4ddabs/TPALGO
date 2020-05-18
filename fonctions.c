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
   Alerte* newalertes;
   int i = 0;
   int k;
   int nmbdeformlocales = 0;
   int premierealerte = 0;
   int premierepos;
   int taillealertes = 0;
   while(premierealerte == 0 && i!=taillepak){
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
         i++;
      }
   }
   if(alertes == NULL){
      printf("pas d'alertes\n");
      return alertes;
   }
   for(i=premierepos;i<taillepak;i++){
      for(k=0;k<taillepak;k++){
         if(abs(paquet[i]-paquet[k])<=100){
            nmbdeformlocales = nmbdeformlocales + 1;
         }
      }
      if(nmbdeformlocales>=100){
         newalertes = Verification(paquet[i],alertes,&taillealertes,nmbdeformlocales);
         if(newalertes != NULL){
            alertes = newalertes;
            newalertes = NULL;
         }
         nmbdeformlocales = 0;
      }
      else{
      nmbdeformlocales = 0;
      }

   }
   printf("nombre d alertes : %d\n", taillealertes);
   return alertes;
}
