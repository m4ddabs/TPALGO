#include "fonctions.h"
#include <stdio.h>
#define LONGUEUR_CABLE 1000000 /* en m */
#define NOMBRE_DEFORMATIONS 100000 /* en nombre de d�formations */

int main()
{
    /* param�tres */
    int nombre_positions = LONGUEUR_CABLE/PRECISION;
    int nombre_deformations = NOMBRE_DEFORMATIONS;
    Simulation simulation = UNIFORME;

    int temps_ecoule; /* pour chronom�trer */
    Alerte* alertes;
    printf("Simulation de %i d�formations sur %i positions, configuration "
        "%i... ", nombre_deformations, nombre_positions, simulation);
    redemarrer_chronometre();
    Position* paquet = simuler_deformations(nombre_positions,nombre_deformations, simulation); //Creation du paquet de positions
    printf("termin�e.\n");
    alertes = ChercheAlerte(paquet, nombre_deformations); // Determination des Alertes
    printf("termin�e.\n");

    temps_ecoule = relever_chronometre_ms();
    printf("Temps �coul� : %i ms.\n", temps_ecoule);

    detruire_deformations(paquet);

    return 0;
}

