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


/**La fonction ChercheAlerte prends comme entree un pointeur sur un paquet et la taille de ce paquet.
Elle sert a chercher les nombre d'alertes et retourne un pointeur a un tableau qui contient toutes les alertes. Si il n'y a pas
d'alertes elle retourne un pointeur sur NULL **/
Alerte* ChercheAlerte(Position* paquet,int taillepak);

/**La fonction Verification est utilisee dans la fonction ChercheAlerte, elle sert a verifier si une alerte existe deja dans le
tableau d'alertes, si elle existe elle n'ajoutera rien au tableau et si elle n'existe pas elle ajoutera la nouvelle alerte au tableau.
Cette fonction prends en entree la position de l'alerte a verifier, un pointeur sur un tableau d'alertes, un pointeur sur la taille
du tableau d'alertes et le nombre deformation locales dans cette position a verifier.
La fonction retourne un pointeur sur le tableau contenant la nouvelle alerte si celle ci n'existait pas avant sinon elle retourne un pointeur
 sur NULL**/

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



