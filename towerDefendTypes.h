#ifndef TOWERDEFENDTYPES_H_INCLUDED
#define TOWERDEFENDTYPES_H_INCLUDED

// Contains all the types needed for the game.

typedef enum{tourSol, tourAir, tourRoi, archer, chevalier, dragon, gargouille} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;


typedef struct {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique la position des unit�s que l�on peut attaquer
    Tcible maposition;		//indique soit � air � soit � sol �, utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c�est petit plus c�est rapide
    int degats;
    int portee ;			//en m�tre, distance sur laquelle on peut atteindre une
                            //cible

    float vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu
    int peutAttaquer;		//permet de g�rer le fait que chaque unit� attaque une
                            //seule fois par tour ;
                            //0 = a d�j� attaqu�, 1 = peut attaquer ce tour-ci
                            // � remettre � 1 au d�but de chaque tour

    //struct Tunite *cible;   //NULL si pas de cible. mettre � jour ce pointeur permet l'aninamtion (simpliste certe) du tir
    //non utilis� au final -> utiliser directement dessineAttaque
} Tunite;


typedef struct T_cell{
    struct T_cell *suiv;
    Tunite *pdata; //pointeur vers une unit�
} *TListePlayer;


typedef Tunite* ** TplateauJeu;  ////tableau a deux dimensions de largeur 11 et hauteur 19 contenant des pointeurs (Tunite*)


#endif // TOWERDEFENDTYPES_H_INCLUDED
