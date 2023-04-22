#ifndef LISTESIMPLE_H_INCLUDED
#define LISTESIMPLE_H_INCLUDED

#include <stdbool.h>
#include "towerDefendTypes.h"

typedef TListePlayer T_liste;

void initListe(T_liste *l);
bool listeVide(T_liste l);

void afficheListe(T_liste l);
void afficheListeShort(T_liste l);

T_liste getPtrLastCell(T_liste l);
T_liste getPtrNextCell(T_liste l);
Tunite* getPtrData(T_liste l);

T_liste ajoutEnTete(T_liste l, Tunite mydata);
T_liste ajoutEnFin(T_liste l, Tunite mydata);
T_liste ajoutEnN(T_liste l, int pos, Tunite mydata);

T_liste ajoutEnTeteParPtr(T_liste l, Tunite *mydata);
T_liste ajoutEnFinParPtr(T_liste l, Tunite *mydata);

T_liste suppEnTete(T_liste l);
T_liste suppEnFin(T_liste l);
T_liste suppEnN(T_liste l, int pos);
T_liste supprimeListe(TListePlayer l);

void swapPtrData(T_liste source, T_liste destination);

int getNbreCell(T_liste l);
int getSizeBytes(T_liste l);

Tunite* listToArray(TListePlayer l, int *length);
T_liste arrayToList(Tunite* arr, int length);

#endif // LISTESIMPLE_H_INCLUDED
