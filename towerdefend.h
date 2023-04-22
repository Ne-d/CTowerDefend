#ifndef TOWERDEFEND_H_INCLUDED
#define TOWERDEFEND_H_INCLUDED

#include "stdbool.h"
#include "towerDefendTypes.h"

#define LARGEURJEU 11
#define HAUTEURJEU 19
#define NBCOORDPARCOURS 34
#define NBPOSITIONSTOWERS 6
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
TplateauJeu PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu);

TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante) ; //retourne la liste des cibles possibles
void combat(SDL_Surface *surface, Tunite * UniteAttaquante, Tunite * UniteCible) ;
TplateauJeu createUnit(TListePlayer *playerRoi, TListePlayer *playerHorde, int **chemin, TplateauJeu plateau);


Tunite *creeArcher(int posx, int posy);
Tunite *creeGargouille(int posx, int posy);
Tunite *creeDragon(int posx, int posy);
Tunite *creeChevalier(int posx, int posy);

TListePlayer supprimerUnite(TListePlayer player, TplateauJeu jeu);
TListePlayer AjouterUnite(TListePlayer player, Tunite *nouvelleUnite);

void deplacement(TListePlayer player,int** chemin, TplateauJeu plateau);

void newTurnCombat(TListePlayer playerHorde, TListePlayer playerRoi);
TListePlayer duringCombat(TListePlayer playerAttack, TListePlayer playerEnemy, TplateauJeu jeu, SDL_Surface *surface);

void saveseq(TListePlayer playerRoi, TListePlayer playerHorde);
void loadseq(TListePlayer* playerRoi, TListePlayer* playerHorde, TplateauJeu jeu);

void savebin(TListePlayer playerRoi, TListePlayer playerHorde);
void loadbin(TListePlayer* playerRoi, TListePlayer* playerHorde, TplateauJeu jeu);


#endif // TOWERDEFEND_H_INCLUDED
