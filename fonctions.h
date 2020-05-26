#include "rapport_deformations.h"

//Fonctions Pour chercher alertes


/**La fonction ChercheAlerte prends comme entree un pointeur sur un paquet et la taille de ce paquet.
Elle sert a chercher les nombre d'alertes et retourne un pointeur a un tableau qui contient toutes les alertes. Si il n'y a pas
d'alertes elle retourne un pointeur sur NULL **/
Alerte* ChercheAlerte(Position* paquet,int taillepak);

/**La fonction Verification est utilisee dans la fonction ChercheAlerte, elle sert a verifier si une alerte existe deja dans le
tableau d'alertes, si elle existe elle n'ajoutera rien au tableau et si elle n'existe pas elle ajoutera la nouvelle alerte au tableau.
Cette fonction prend en entree la position de l'alerte a verifier, un pointeur sur un tableau d'alertes, un pointeur sur la taille
du tableau d'alertes et le nombre deformation locales dans cette position a verifier.
La fonction retourne un pointeur sur le tableau contenant la nouvelle alerte si celle ci n'existait pas avant sinon elle retourne un pointeur
 sur NULL**/

Alerte* Verification(Position pos, Alerte* alerte,int* taille_tab_alerte,int nmbdeformlocales);
