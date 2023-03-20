#ifndef LISTESIMPLE_H_INCLUDED
#define LISTESIMPLE_H_INCLUDED

#include "towerDefendTypes.h"

typedef T_liste TListePlayer;

void initListe(T_liste *l);
bool listeVide(T_liste l);
void afficheListe(T_liste l);

T_liste ajoutEnTete(T_liste l, Tunite mydata);
T_liste ajoutEnFin(T_liste l, Tunite mydata);
T_liste ajoutEnN(T_liste l, int pon, Tunite mydata);

T_liste suppEnTete(T_liste l);
T_liste suppEnFin(T_liste l);
T_liste suppEnN(T_liste l, int pos);

T_liste getPtrFirstCell(T_liste l);
T_liste getPtrLastCell(T_liste l);
T_liste getPtrNextCell(T_liste l);
T_liste getPtrPrevCell(T_liste l);

Tunite* getPtrData(T_liste l);
void swapPtrData(T_liste source, T_liste destination);

int getNbreCell(T_liste l);
int getSizeBytes(T_liste l);

T_liste findCell(T_liste l, int data);
int getOccurrences(T_liste l, int data);

#endif // LISTESIMPLE_H_INCLUDED
