#include <stdio.h>
#include "fonctions.h"
#include <math.h>
#include <stdlib.h>
//Fonctions pour la cherche d'alertes

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

//Fonctions pour la simulation du paquet

static clock_t temps_cpu;

void redemarrer_chronometre()
{
    temps_cpu = clock();
}

int relever_chronometre_ms()
{
    return (clock() - temps_cpu)/((double) CLOCKS_PER_SEC)*1000;
}

/* tire aléatoirement une valeur réelle selon une distribution triangulaire
 * centrée en 1/2 et de largeur 1 */
double distribution_triangulaire(){
    int valeur;
    int accepte = 0;
    while (!accepte){
        valeur = rand();
        if (valeur <= RAND_MAX/2){
            accepte = (rand() % RAND_MAX/2) <= valeur;
        }else{
            accepte = (rand() % RAND_MAX/2) <= RAND_MAX - valeur;
        }
    }
    return valeur/(double) RAND_MAX;
}

/* tire aléatoirement une position selon une distribution triangulaire */
Position position_distr_triang(Position centre, int largeur)
{
    return centre - largeur/2 + (int) (largeur*distribution_triangulaire());
}

/* transformation d'un tableau de positions tirées uniformément en une
 * distribution quasi-monotone */
/* fonction auxiliaire : ordonne les positions autour d'une valeur pivot */
int distribuer_pivot(Position* positions, int n)
{
    Position pivot = positions[0];
    int i = 1;
    int j = n;
    while (i < j){
        if (positions[i] <= pivot){
            i++;
        }else{
            j--;
            Position tmp = positions[j];
            positions[j] = positions[i];
            positions[i] = tmp;
        }
    }
    if (i == n){
        positions[0] = positions[n - 1];
        positions[n - 1] = pivot;
        return n - 1;
    }
    return i;
}

/* transformation : tri partiel */
void transf_quasi_monotone(Position* deformations, int nombre_deformations,
    int arret)
{
    if (nombre_deformations < arret){ return; }
    int i = distribuer_pivot(deformations, nombre_deformations);
    transf_quasi_monotone(deformations, i, arret);
    transf_quasi_monotone(deformations + i, nombre_deformations - i, arret);
}

Position* simuler_deformations(Position nombre_positions,
    int nombre_deformations, Simulation simulation)
{
    Position* paquet = malloc(sizeof(Position)*nombre_deformations);
    if (!paquet){
        fprintf(stderr, "Nombre de déformations trop grand, pas assez de "
            "mémoire.\n");
        exit(EXIT_FAILURE);
    }
    int i;
    if (simulation == UNIFORME){
        /* distribution uniforme */
        for (i = 0; i < nombre_deformations; i++){
            paquet[i] = rand() % nombre_positions;
        }
    }else{
        if (simulation == MONOMODALE){
            /* distribution triangulaire centrée sur la position centrale,
             * largeur quart */
            Position centre = nombre_positions/4;
            int largeur = nombre_positions/4;
            for (i = 0; i < nombre_deformations; i++){
                paquet[i] = position_distr_triang(centre, largeur);
            }
        }else if (simulation == BIMODALE){
            /* deux distributions triangulaires centrées sur les positions en
             * premier et troisième quartile, largeur huitième */
            int largeur = nombre_positions/8;
            for (i = 0; i < nombre_deformations; i++){
                Position centre = (rand() % 2) ?
                    nombre_positions/4 : 3*nombre_positions/4;
                paquet[i] = position_distr_triang(centre, largeur);
            }
        }else if (simulation == QUASIMONOTONE){
            for (i = 0; i < nombre_deformations; i++){
                paquet[i] = rand() % nombre_positions;
            }
            /* une valeur d'arrêt assez grande assure des inversions */
            int arret = SEUIL_ALERTE;
            transf_quasi_monotone(paquet, nombre_deformations, arret);
        }else{
            fprintf(stderr, "Configuration %i invalide.\n", simulation);
            exit(EXIT_FAILURE);
        }
    }

    return paquet;
}

void detruire_deformations(Position* paquet)
{
    free(paquet);
}
