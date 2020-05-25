#include <time.h> /* pour la mesure du temps de calcul */
#define PRECISION 1 /* en m */
#define DIST_MAX_VOISIN 100 /* en m */
#define SEUIL_ALERTE 100 /* en nombre de d�formations */

/***  mesure du temps de calcul  ***/
void redemarrer_chronometre();
int relever_chronometre_ms();  /* en millisecondes */


// Modelisation de l'alerte

typedef int Position;

struct Alerte{
    Position position;
    int nombre_deformations_locales;
};

typedef struct Alerte Alerte;

//Fonctions Pour chercher alertes

Alerte* ChercheAlerte(Position* paquet,int taillepak);

Alerte* Verification(Position pos, Alerte* alerte,int* taille_tab_alerte,int nmbdeformlocales);

/***  simulation d'un paquet de deformations  ***/

/* diff�rentes configurations des d�formations */
enum Simulation {UNIFORME, MONOMODALE, BIMODALE, QUASIMONOTONE};
typedef enum Simulation Simulation;

/* Simulation proprement dite
 *
 *     ENTREES
 * nombres_positions : le nombre de positions possibles (les positions sont
 *     rep�r�es par des entiers entre 0 et nombre_positions - 1)
 * nombre_deformations : le nombre de d�formations simul�es
 * simulation : configuration des d�formations consid�r�es
 *
 *     SORTIE
 * pointeur sur un paquet de deformations, c'est-�-dire un tableau de positions
 * comprises entre 0 et nombres_positions - 1, de taille nombre_deformations */
Position* simuler_deformations(Position nombre_positions,
    int nombre_deformations, Simulation simulation);

/* Lib�re la m�moire utilis�e par un paquet de d�formations */
void detruire_deformations(Position* paquet);



