#include "stdio.h"
#include "testListeSimple.h"
#include "listeSimple.h"

int testListeSimple() {
    T_liste l;
    initListe(&l);

    afficheListe(l);

    return 0;
}
