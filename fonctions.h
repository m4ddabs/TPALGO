typedef int Position;

struct Alerte{
    Position position;
    int nombre_deformations_locales;
};

typedef struct Alerte Alerte;


Alerte* ChercheAlerte(Position* paquet,int taillepak);

int verification(Position pos, Alerte* alerte,int* taille_tab_alerte,int nmbdeformlocales)



