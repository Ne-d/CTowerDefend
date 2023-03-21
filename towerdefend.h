#ifndef TOWERDEFEND_H_INCLUDED
#define TOWERDEFEND_H_INCLUDED

#include "stdbool.h"
#include "towerDefendTypes.h"

#define LARGEURJEU 11
#define HAUTEURJEU 19
#define NBCOORDPARCOURS 35
#define X 0
#define Y 1

TplateauJeu AlloueTab2D(int largeur, int hauteur);
void afficheCoordonneesParcours(int **t, int nbcoord);
int **initChemin();         //retourne le chemin emprunter par la horde, sous forme d'un tableau[NBCOORDPARCOURS][2]

void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);

Tunite *creeTourSol(int posx, int posy);
Tunite *creeTourAir(int posx, int posy);
Tunite *creeTourRoi(int posx, int posy);


bool tourRoiDetruite(TListePlayer player);
/*void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu)

TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante) ; //retourne la liste des cibles possibles
Void combat(SDL_Surface *surface , Tunite * UniteAttaquante, Tunite * UniteCible) ;

*/
Tunite *creeArcher(int posx, int posy);
Tunite *creeGargouille(int posx, int posy);
Tunite *creeDragon(int posx, int posy);
Tunite *creeChevalier(int posx, int posy);

/*
Void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite);
Void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);

*/

// Debug
void printUnite(Tunite u);

#endif // TOWERDEFEND_H_INCLUDED
