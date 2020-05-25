#include "fonctions.h"
#include <stdio.h>
#define LONGUEUR_CABLE 1000000 /* en m */
#define NOMBRE_DEFORMATIONS 100000 /* en nombre de déformations */

int main()
{
    /* paramètres */
    int nombre_positions = LONGUEUR_CABLE/PRECISION;
    int nombre_deformations = NOMBRE_DEFORMATIONS;
    Simulation simulation = UNIFORME;

    int temps_ecoule; /* pour chronométrer */
    Alerte* alertes;
    printf("Simulation de %i déformations sur %i positions, configuration "
        "%i... ", nombre_deformations, nombre_positions, simulation);
    redemarrer_chronometre();
    Position* paquet = simuler_deformations(nombre_positions,nombre_deformations, simulation); //Creation du paquet de positions
    printf("terminée.\n");
    alertes = ChercheAlerte(paquet, nombre_deformations); // Determination des Alertes
    printf("terminée.\n");

    temps_ecoule = relever_chronometre_ms();
    printf("Temps écoulé : %i ms.\n", temps_ecoule);

    detruire_deformations(paquet);

    return 0;
}

