#include "rapport_deformations.h"
//la fonction verification permet de s'assurer qu'il n'y ai pas de doublons dans les alertes. Si l'alerte passée en parametre n'existe pas dans le tableau d'alertes, elle augmente la taille du tableau, ajoute l'alerte et renvoie un pointeur vers le nouveau tableau. Sinon, elle ne fait rien.
Alerte* verification (Position pos, Alerte* alerte,int* taille_tab_alerte,int nmbdeformlocales);
//permute deux variables, fonction utilisee par triRapid
void permuter(int *a, int *b);
//trie dans l'ordre croissant un tableau
void triRapid(int tab[], int first, int last);
//cherche les alertes et utilise verification
Alerte* reperer_alertes (Position* paquet, Alerte* alerte, int* taille_tab_alerte);
