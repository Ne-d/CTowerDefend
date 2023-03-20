#ifndef LISTEPLAYER_H_INCLUDED
#define LISTEPLAYER_H_INCLUDED

#include "towerdefend.h"
#include "towerDefendTypes.h"

void initListe(TListePlayer *liste);

Tunite* getUnitePtr(TListePlayer cell);
TListePlayer getNextCell(TListePlayer cell);

TListePlayer ajoutEnTete(TListePlayer liste, Tunite data);
TListePlayer ajoutEnFin(TListePlayer liste, Tunite data);

#endif // LISTEPLAYER_H_INCLUDED
