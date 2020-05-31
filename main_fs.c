#include "fonctions_fs.h"
#include <stdio.h>
#include<stdlib.h>
#define LONGUEUR_CABLE 1000000 /* en m */
#define NOMBRE_DEFORMATIONS 100000 /* en nombre de déformations */

int main()
{
    /* paramètres */
    int nombre_positions = LONGUEUR_CABLE/PRECISION;
    int nombre_deformations = NOMBRE_DEFORMATIONS;
    Simulation simulation = UNIFORME;

    int temps_ecoule; /* pour chronométrer */

    printf("Simulation de %i deformations sur %i positions, configuration "
        "%i... ", nombre_deformations, nombre_positions, simulation);
    redemarrer_chronometre();
    Position* paquet = simuler_deformations(nombre_positions,
        nombre_deformations, simulation);
    printf("terminee.\n");
    triRapid(paquet,0,nombre_deformations-1);
    const char* nom_fichier = "simulation_deformations.txt";
    printf("Ecriture du paquet de deformations trie dans %s... ", nom_fichier);
    int i;
    FILE* file = fopen(nom_fichier, "w");
    for (i = 0; i < nombre_deformations; i++){
        fprintf(file, "%i ", paquet[i]);
    }
    fclose(file);
    printf("terminee.\n");

    temps_ecoule = relever_chronometre_ms();
    printf("Temps ecoule : %i ms.\n", temps_ecoule);
    Alerte* alerte=NULL;
    int taille=0;
    Alerte* nouveau_alerte = reperer_alertes(paquet,alerte,&taille); //cherche les alertes dans le paquet et récupère dans un tableau pointé par nouveau_alerte
    printf("nombre total d'alertes : %d\n",taille);
    free(alerte);
    free(nouveau_alerte);
    detruire_deformations(paquet);

    return 0;
}
