#include <stdio.h>
#include "fonctions.h"
#include <math.h>
#include <stdlib.h>
//Fonctions pour la cherche d'alertes

Alerte* Verification(Position pos, Alerte* alerte,int* taille_tab_alerte,int nmbdeformlocales)
{
    int i;
    for (i=0;i<(*taille_tab_alerte);i++) //Boucle pour chercher si l'alerte est deja dans le tableau
    {
        if (pos==(alerte+i)->position)
        {
            return NULL;                  //Si elle existe on retourne NULL
        }
    }
    Alerte* newalerte                      //Creation de un nouveau pointeur qui va contenir l'adresse a retourner
    *taille_tab_alerte=*taille_tab_alerte+1;
    newalerte = realloc(alerte,sizeof(Alerte)*(*taille_tab_alerte));//la fonction realloc va retourner un nouveau tableau avec la nouvelle alerte
    if(newalerte == NULL)                                           //Dans le cas ou realloc ne marche pas elle retourne NULL donc ce if sert a gerer cette situation
    {
       printf("un probleme est survenu lors de l'allocation de memoire\n");
       return NULL;
    }
    (newalerte+i)->position=pos;                                     // Si on ne rentre pas dans le if le programme continue normalement et ajoute les info de la nouvelle alerte dans le tableau
    (newalerte+i)->nombre_deformations_locales = nmbdeformlocales;
    return newalerte;
}

Alerte* ChercheAlerte(Position* paquet,int taillepak){
   /** Inittialisation des variable **/
   Alerte* alertes = NULL;
   Alerte* newalertes;
   int i = 0;
   int k;
   int nmbdeformlocales = 0;
   int premierealerte = 0;
   int premierepos;
   int taillealertes = 0;

   /** Premiere boucle **/
   /** Elle serte a chercher la premiere alerte. Si il n'y a pas d'alerte
        alertes reste initialise sur NULL donc le programme se terminera **/

   while(premierealerte == 0 && i!=taillepak){
      for(k=0;k<taillepak;k++){
         if(abs(paquet[i]-paquet[k])<=100){          //Ici nous cherchon la distance entre une position donnee et totues les autres positions du paquet
            nmbdeformlocales = nmbdeformlocales + 1; //Si cette distance <100 ou = 100 donc on la compte pour former une alerte
         }
      }
      if(nmbdeformlocales>=100){            //On est encore sur une position donnee, si le nomvre de deformations locales > 100 ou = 100
         alertes = malloc(sizeof(Alerte));  //Nous allons creer une nouvelle alerte et sortir de la premiere boucle
         taillealertes = taillealertes + 1;
         alertes[0].position = paquet[i];
         alertes[0].nombre_deformations_locales = nmbdeformlocales;
         nmbdeformlocales = 0;
         premierepos = i+1;
         premierealerte = 1;
      }
      else{                                 //Sinon nous continuerons jusqu'a trouver un alerte
         nmbdeformlocales=0;
         i++;
      }
   }
   if(alertes == NULL){                    // Si il n'y a pas eu d'alertes nous arrettons le programme
      printf("pas d'alertes\n");
      return alertes;
   }

   /**Deuxieme boucle**/
   /** Elle sert a chercher le reste des alertes
   Elle presque identique a la premiere boucle sauf que ici nous n'arreterons pas si on trouve une alerte et nous allons verfier
   si une alerte donnee existe deja dans le tableau d'alertes avant de la rentrer dans celui ci**/

   for(i=premierepos;i<taillepak;i++){ // On parcours le paquet
      for(k=0;k<taillepak;k++){
         if(abs(paquet[i]-paquet[k])<=100){
            nmbdeformlocales = nmbdeformlocales + 1;
         }
      }
      if(nmbdeformlocales>=100){
         newalertes = Verification(paquet[i],alertes,&taillealertes,nmbdeformlocales); // On fait appel a Verification
         if(newalertes != NULL){ //Si nous avons un nouveau tableau nous passons l'adresse a alertes et on repointe newalertes a NULL
            alertes = newalertes;
            newalertes = NULL;
         }
         nmbdeformlocales = 0; //Sinon newalertes reste sur NULL
      }
      else{
      nmbdeformlocales = 0;
      }

   }                                               //on retourne l'adresse d'alertes et on donne le nombre d'alertes
   printf("nombre d alertes : %d\n", taillealertes);
   return alertes;
}
