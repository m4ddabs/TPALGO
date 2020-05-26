#include "fonctions.h"
#include <stdlib.h>
#include <stdio.h>
#define LONGUEUR_CABLE 1000000 /* en m */
#define NOMBRE_DEFORMATIONS 100000 /* en nombre de déformations */

Alerte* verification (Position pos, Alerte* alerte,int* taille_tab_alerte,int nmbdeformlocales)
{
    int i;
    for (i=0;i<(*taille_tab_alerte);i++)
    {
        if (pos==(alerte+i)->position)
        {
            return NULL; //si la position est déjà dans le tableau d'alertes, on ne fait rien
        }
    }
    *taille_tab_alerte=*taille_tab_alerte+1; //la position n'est pas encore présente, on incrémente de 1 la taille du tableau
    Alerte* new_alerte=realloc(alerte,(*taille_tab_alerte)*sizeof(Alerte)); //on alloue dynamiquement au tableau l'espace supplémentaire nécessaire
    (new_alerte+i)->position=pos; //on ajoute les informations sur l'alerte dans le tableau
    (new_alerte+i)->nombre_deformations_locales=nmbdeformlocales;
    return new_alerte; //le pointeur vers le tableau actualisé est retourné
}

void permuter(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void triRapid(int tab[], int first, int last) {
    int pivot, i, j;
    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while(tab[i] <= tab[pivot] && i < last)
                i++;
            while(tab[j] > tab[pivot])
                j--;
            if(i < j) {
                permuter(&tab[i], &tab[j]);
            }
        }
        permuter(&tab[pivot], &tab[j]);
        triRapid(tab, first, j - 1);
        triRapid(tab, j + 1, last);
    }
}

Alerte* reperer_alertes (Position* paquet, Alerte* alerte, int* taille_tab_alerte)
{
    int i,j,voisins=0;
    Alerte* test;
    for(i=0;i<NOMBRE_DEFORMATIONS;i++) //on parcourt tout le paquet
    {
        j=i;
        while((paquet[i]-DIST_MAX_VOISIN)<=paquet[j] && j>0)
        {
            voisins++;
            j--;
            //on récupère les voisins à gauche de la position étudiée
        }
        j=i+1;
        while(paquet[j]<=(paquet[i]+DIST_MAX_VOISIN) && j<NOMBRE_DEFORMATIONS)
        {
            voisins++;
            j++;
            //on récupère les voisins à droite de la position étudiée
        }
        if(voisins>=100) //si une alerte est déclarée
        {
            if(alerte==NULL) //s'il s'agit de la première alerte
            {
                alerte=malloc(sizeof(Alerte));
                *taille_tab_alerte=1;
                alerte->nombre_deformations_locales=voisins;
                alerte->position=paquet[i];
            }
            else
            {
                test=verification(paquet[i],alerte,taille_tab_alerte,voisins); //on vérifie si l'alerte est un doublon ou non
                if(test!=NULL) //si l'alerte n'est pas un doublon
                {
                    alerte=test; //on actualise le pointeur
                }
            }
        }
        voisins=0; //réinitialisation du nombre de voisins avant de passer à la position suivante
    }
    return alerte; //retourne le pointeur vers le tableau complet d'alertes après avoir étudié toutes les positions
}
