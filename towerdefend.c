#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "maSDL.h"
#include "towerdefend.h"
#include "listeSimple.h"


//typedef Tunite* ** TplateauJeu;

TplateauJeu AlloueTab2D(int largeur, int hauteur)
{
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0; i<largeur; i++)
    {
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur)
{
    for (int i=0; i<largeur; i++)
    {
        for (int j=0; j<hauteur; j++)
        {
            jeu[i][j] = NULL;
        }
    }

    //POUR LA DEMO D'AFFICHAGE UNIQUEMENT, A SUPPRIMER
    //(les tours ici ne sont pas liées aux listes des unités de vos joueurs)
    /*
    jeu[5][3]=creeTourSol(5,3);
    jeu[3][3]=creeTourAir(3,3);
    jeu[4][1]=creeTourRoi(4,1);
    jeu[4][15]=creeTourAir(4,15);
    jeu[5][17]=creeDragon(5,17);
    */
    //FIN DEMO AFFICHAGE
}


/*
void ecritCheminVersleHaut  : permet d'initilaiser le tab chemin de distance cases (avec des coord x y) dans une direction, à partir d'un point x y donné

int **chemin  : tab de coordonnées x y du chemin
int *ichemin  : indice de la case du chemin d'où on part
int *xdepart, int *ydepart : valeur en x y de départ pouri la premiere case
int distance  : distance sur laquelle on va écrire des coordonnées dans le tab chemin
int *distanceMaxRestante : securité pour ne pas sortir de la plage d'indice de chemin
*/
void ecritCheminVersleHaut(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante)
{
    if ((*distanceMaxRestante - distance)>=0)
    {
        int y;
        for (y=*ydepart; y>*ydepart-distance; y--)
        {
            chemin[*ichemin][X]= *xdepart;
            chemin[*ichemin][Y]= y;
            (*ichemin)++;
        }
        *ydepart=y;
    }
    else printf("erreur longueur chemin\n");
}
void ecritCheminVerslaDroite(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante)
{
    if ((*distanceMaxRestante - distance)>=0)
    {
        int x;
        for (x=*xdepart; x<*xdepart+distance; x++)
        {
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}
void ecritCheminVerslaGauche(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante)
{
    if ((*distanceMaxRestante - distance)>=0)
    {
        int x;
        for (x=*xdepart; x>*xdepart-distance; x--)
        {
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}

int **initChemin()
{
    int **chemin = (int**)malloc(sizeof(int*)*NBCOORDPARCOURS);

    for (int j=0; j<NBCOORDPARCOURS; j++)
    {
        chemin[j] = (int*)malloc(sizeof(int)*2);  //2 cases :indice 0 pour la coord en X, indice 1 pour la coord en Y
    }

    int ydepart = 18;  //18 on part du bas
    int xdepart = 5;  //5 = milieu de la fenetre de 11 de largeur (0-10)
    int i = 0;  //parcourt les i cases du chemin
    int distanceMaxRestante = NBCOORDPARCOURS;

    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 5, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);

    return chemin;  //tab2D contenant des pointeurs
}

void afficheCoordonneesParcours(int **chemin, int nbcoord)
{
    printf("Liste coordonnees: ");
    for (int i=0; i<nbcoord; i++)
    {
        printf("(%d, %d)",chemin[i][X], chemin[i][Y]);
    }
    printf("\nfin liste coordonnées\n");
}


void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur)
{
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[7]= {"s", "a", "r", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0; j<hauteur; j++)
    {
        for (int i=0; i<largeur; i++)
        {
            // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL)
            {
                printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}

// Les fonctions suivantes créent les unités avec leurs stats en leur allouant un espace mémoire
Tunite *creeTourSol(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourSol;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 120;
    nouv->portee = 5;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeTourAir(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourAir;
    nouv->cibleAttaquable = air;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeTourRoi(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 180;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeDragon(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 70;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeArcher(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeGargouille(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeChevalier(int posx, int posy)
{
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

//Retourne True si le Roi est tué
bool tourRoiDetruite(TListePlayer playerRoi)
{
    return playerRoi->pdata->pointsDeVie <= 0;
}

//Supprime l'unité quand sa vie est à 0, Si c'est la dernière unité, la liste du joueur est NULL
//A Test
void supprimerUnite(TListePlayer player, Tunite *UniteDetruite, TplateauJeu jeu)
{
    TListePlayer new_list = player;
    int x = UniteDetruite->posX;
    int y = UniteDetruite->posY;
    int index = 0;

    //On vérifie si l'unité n'a plus de PV
    if(UniteDetruite->pointsDeVie <=0)
    {
        // Trouve l'index de l'unité à détruire dans la liste en comparant les coordonnées
        while(x != getPtrData(new_list)->posX && y != getPtrData(new_list)->posY && getPtrNextCell(new_list) != NULL)
        {
            new_list = getPtrNextCell(new_list);
            index ++;
        }
        jeu[x][y] = NULL;
        player = suppEnN(player,index);
    }
}

//Cette fonction fait combattre 2 unités entre elles
//A test
void combat(SDL_Surface *surface, Tunite * UniteAttaquante, Tunite * UniteCible)
{
    //On vérifie si l'unité n'a pas déjà attaqué dans le tour
    if(UniteAttaquante->peutAttaquer == 1)
    {
        UniteCible->pointsDeVie = UniteCible->pointsDeVie - UniteAttaquante->degats;
        UniteAttaquante->peutAttaquer = 0;
        dessineAttaque(surface,UniteAttaquante,UniteCible);
    }
}

// This function creates an unit randomly for each players.
// A test
TplateauJeu createUnit(TListePlayer *playerRoi, TListePlayer *playerHorde, int **chemin, TplateauJeu plateau)
{
    // Generate a random number between 0 and 100 for each team.
    int randNbR = rand() % 100;
    int randNbH = rand() % 100;

    // Chooses if a new tower will spawn
    if(randNbR > 101)  // TODO: This will never be true, for debug purposes. Change that for release.
    {
        printf("createUnit: a new tower will spawn.\n");
        // Find a set of coordinates to spawn the new tower on
        bool validPositionFound = false;
        while(!validPositionFound)
        {
            // Trouve une case du chemin aléatoire et ses coordonnées.
            int pathIndex = rand() % NBCOORDPARCOURS;
            int cheminX = chemin[pathIndex][X];
            int cheminY = chemin[pathIndex][Y];

            int finalX = -1;
            int finalY = -1;

            // Teste si la case à droite de la case du chemin choisie est disponible (pas du chemin, et pas occupée)
            int newX = cheminX + 1;
            int newY = cheminY;
            if( !( (newX == chemin[pathIndex + 1][X] && newY == chemin[pathIndex + 1][Y]) || // Vérifie si les coordonnées choisies sont
                    (newX == chemin[pathIndex - 1][X] && newY == chemin[pathIndex - 1][Y]) ) && // Celles de la case d'avant ou d'après du chemin
                    (plateau[newX][newY] == NULL)) // Et que la case n'es pas déjà occupée
            {
                validPositionFound = true;
                finalX = newX;
                finalY = newY;
            }

            // Teste si la case à gauche de la case du chemin choisie est disponible (pas du chemin, et pas occupée)
            newX = cheminX - 1;
            newY = cheminY;
            if( !( (newX == chemin[pathIndex + 1][X] && newY == chemin[pathIndex + 1][Y]) || // Vérifie si les coordonnées choisies sont
                    (newX == chemin[pathIndex - 1][X] && newY == chemin[pathIndex - 1][Y]) ) && // Celles de la case d'avant ou d'après du chemin
                    (plateau[newX][newY] == NULL)) // Et que la case n'es pas déjà occupée
            {
                validPositionFound = true;
                finalX = newX;
                finalY = newY;
            }

            // Teste si la case au dessus de la case du chemin choisie est disponible (pas du chemin, et pas occupée)
            newX = cheminX;
            newY = cheminY - 1;
            if( !( (newX == chemin[pathIndex + 1][X] && newY == chemin[pathIndex + 1][Y]) || // Vérifie si les coordonnées choisies sont
                    (newX == chemin[pathIndex - 1][X] && newY == chemin[pathIndex - 1][Y]) ) && // Celles de la case d'avant ou d'après du chemin
                    (plateau[newX][newY] == NULL)) // Et que la case n'es pas déjà occupée
            {
                validPositionFound = true;
                finalX = newX;
                finalY = newY;
            }

            // Teste si la case en dessous de la case du chemin choisie est disponible (pas du chemin, et pas occupée)
            newX = cheminX;
            newY = cheminY + 1;
            if( !( (newX == chemin[pathIndex + 1][X] && newY == chemin[pathIndex + 1][Y]) || // Vérifie si les coordonnées choisies sont
                    (newX == chemin[pathIndex - 1][X] && newY == chemin[pathIndex - 1][Y]) ) && // Celles de la case d'avant ou d'après du chemin
                    (plateau[newX][newY] == NULL)) // Et que la case n'es pas déjà occupée
            {
                validPositionFound = true;
                finalX = newX;
                finalY = newY;
            }

            if(validPositionFound)
            {
                printf("createUnit: valid position found to spawn a new tower.\n");
            }

            if((rand()%100) > 50)
            {
                *playerRoi = AjouterUnite(*playerRoi, creeTourAir(finalX, finalY));
                printf("createUnit: spawning a new air tower.\n");
            }
            else
            {
                *playerRoi = AjouterUnite(*playerRoi, creeTourSol(finalX, finalY));
                printf("createUnit: spawning a new ground tower.\n");
            }

        }

    }

    int spawnX = chemin[0][X];
    int spawnY = chemin[0][Y];
    // Choisis si une nouvelle unité de la horde va apparaitre, en fonction d'une probabilité et en vérifiant que la case est libre.
    if(randNbH < 10 && plateau[spawnX][spawnY] == NULL)
    {
        Tunite* newUnit = NULL;
        printf("createUnit: a new unit of the horde will spawn.\n");
        int valueUnit = rand() % 100;
        if(valueUnit < 25)
        {
            newUnit = creeGargouille(spawnX, spawnY);
            *playerHorde = AjouterUnite(*playerHorde, newUnit);
            printf("createUnit: spawning a new gargoil.\n");
        }
        else if(valueUnit > 25 && valueUnit < 50)
        {
            newUnit = creeArcher(spawnX, spawnY);
            *playerHorde = AjouterUnite(*playerHorde, newUnit);
            printf("createUnit: spawning a new archer.\n");
        }
        else if(valueUnit > 50 && valueUnit < 75)
        {
            newUnit = creeChevalier(spawnX, spawnY);
            *playerHorde = AjouterUnite(*playerHorde, newUnit);
            printf("createUnit: spawning a new knight.\n");
        }
        else
        {
            newUnit = creeDragon(spawnX, spawnY);
            *playerHorde = AjouterUnite(*playerHorde, newUnit);
            printf("createUnit: spawning a new dragon.\n");
        }

        plateau[spawnX][spawnY] = newUnit;
    }

    //plateau = PositionnePlayerOnPlateau(playerHorde, plateau);
    //plateau = PositionnePlayerOnPlateau(playerRoi, plateau);

    return plateau;
}

//A test
//Cette fonction ajoute une unité choisit par createUnit() dans la liste des joueurs concernés
TListePlayer AjouterUnite(TListePlayer player, Tunite *nouvelleUnite)
{
    //On vérifie si l'unité est à ajouter au début de la liste (le roi et les membres de la horde) ou en deuxième position (les tours)
    if(nouvelleUnite->nom == tourAir || nouvelleUnite->nom == tourSol)
    {
        player = ajoutEnN(player, 1, *nouvelleUnite);
    }
    else
    {
        player = ajoutEnFin(player, *nouvelleUnite);
    }

    return player;
}

//Cette fonction permet aux unités de la Horde de se déplacer sur le chemin du jeu
// TODO: A tester
void deplacement(TListePlayer player, int** chemin, TplateauJeu plateau)
{

    if(!listeVide(player))
    {
        printf("Starting deplacement().\n");

        //On parcourt toutes les unités du joueur
        TListePlayer newlist = player;
        while(newlist != NULL)
        {
            Tunite* currentUnit = getPtrData(newlist);
            int originX = currentUnit->posX;
            int originY = currentUnit->posY;

            //On parcourt les cases du chemin pour en trouver l'indice de la case de l'unité
            int indiceCaseUnit = 0;
            while(originX != chemin[indiceCaseUnit][X] || originY != chemin[indiceCaseUnit][Y])
            {
                indiceCaseUnit ++;
            }

            //On vérifie de combien on peut avancer l'unité suivant sa capacité de déplacement, si les cases sont occupées ou non et si la fin du chemin est atteinte
            int casesMax = 0;

            while(indiceCaseUnit + casesMax + 1 < NBCOORDPARCOURS && // Vérifie si on ne va pas dépasser le bout du chemin
                    plateau[chemin[indiceCaseUnit + casesMax + 1][X]][chemin[indiceCaseUnit + casesMax + 1][Y]] == NULL && // Vérifie si la case est libre
                    casesMax + 1 <= currentUnit->vitessedeplacement) // Vérifie si on a atteint le nombre de cases maximum pour ce tour
            {
                casesMax++;
            }

            //On effectue le déplacement en changeant posX et posY dans l'unité
            int newX = chemin[indiceCaseUnit + (casesMax)][X];
            int newY = chemin[indiceCaseUnit + (casesMax)][Y];

            currentUnit->posX = newX;
            currentUnit->posY = newY;

            // On effectue le déplacement de manière graphique en supprimant l'unité de son ancienne case et en la rajoutant aux nouvelles coordonnées.
            plateau[originX][originY] = NULL;
            plateau[newX][newY] = currentUnit;

            newlist = getPtrNextCell(newlist);
        }
    }

    printf("Finished deplacement().\n");
}

// TODO: This is untested.
//Retourne une liste des unités à portée pour l'unité attaquante
TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante)
{
    TListePlayer l;
    initListe(&l);

    // Loop through all coordinates of the TplateauJeu
    // TODO: This could be made more efficient by only looking at a square around the attacking unit.
    for(unsigned int i = 0; i < LARGEURJEU; i++) // X coordinate
    {
        for(unsigned int j = 0; j < HAUTEURJEU; i++) // Y coordinate
        {
            Tunite* cible = jeu[i][j];

            // Checking if the target is in a position we can attack (ground or air, not coordinates)
            if(UniteAttaquante->cibleAttaquable == cible->maposition || UniteAttaquante->cibleAttaquable == solEtAir)
            {
                bool cibleIsEnemy = false;

                // Checking if the attacker is in the king's team and the target is in the horde.
                if( (UniteAttaquante->nom == tourRoi || UniteAttaquante->nom == tourSol || UniteAttaquante->nom == tourAir) &&
                        (cible->nom == archer || cible->nom == chevalier || cible->nom == dragon || cible->nom == gargouille) )
                {
                    cibleIsEnemy = true;
                }

                // Alternatively, checking if the attacker is in the horde and the target is the king's tower
                // (they don't attack the other towers)
                if( (UniteAttaquante->nom == archer || UniteAttaquante->nom == chevalier ||
                        UniteAttaquante->nom == dragon || UniteAttaquante->nom == gargouille) &&
                        cible->nom == tourRoi )
                {
                    cibleIsEnemy = true;
                }
                // This feels overly complicated, but I haven't found anything better.

                if(cibleIsEnemy)
                {
                    int deltaX = UniteAttaquante->posX - cible->posX;
                    int deltaY = UniteAttaquante->posY - cible->posY;
                    int distanceSquared = abs(deltaX * deltaX + deltaY * deltaY);

                    // Checking if the target is in range but is not the attacker itself
                    if(distanceSquared <= (UniteAttaquante->portee * UniteAttaquante->portee) && distanceSquared != 0)
                    {
                        l = ajoutEnTete(l, *cible);
                    }
                }
            }
        }
    }

    return l;

}

// A tester
// TODO: Passer un pointeur serait plus optimisé pour éviter de copier tout le tableau
TplateauJeu PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu)
{
    TListePlayer newlist = player;
    int x = getPtrData(newlist)->posX;
    int y = getPtrData(newlist)->posY;

    jeu[x][y] = getPtrData(newlist);

    while(getPtrNextCell(newlist) != NULL)
    {
        x = getPtrData(newlist)->posX;
        y = getPtrData(newlist)->posY;

        jeu[x][y] = getPtrData(newlist);
        newlist = getPtrNextCell(newlist);
    }

    return jeu;
}

void newTurnCombat(TListePlayer playerHorde, TListePlayer playerRoi){
    do{
        getPtrData(playerHorde)->peutAttaquer = 1;
        if(getPtrNextCell(playerHorde) != NULL) playerHorde = getPtrNextCell(playerHorde);
    }while(getPtrNextCell(playerHorde) != NULL);

    do{
        getPtrData(playerRoi)->peutAttaquer = 1;
        if(getPtrNextCell(playerRoi) != NULL) playerRoi = getPtrNextCell(playerRoi);
    }while(getPtrNextCell(playerRoi) != NULL);
}

void duringCombat(TListePlayer player, TplateauJeu jeu, SDL_Surface *surface){
    do{
        TListePlayer targetList = quiEstAPortee(jeu,getPtrData(player));
        Tunite *lowUnit = NULL;
        if(!listeVide(targetList)){
            do{
                if(getPtrData(targetList)->pointsDeVie < lowUnit->pointsDeVie){
                        lowUnit = getPtrData(targetList);
                }
                if(getPtrNextCell(targetList) != NULL) targetList = getPtrNextCell(targetList);
            }while(getPtrNextCell(targetList) != NULL);
            combat(surface,getPtrData(player),lowUnit);
            supprimerUnite(player,lowUnit,jeu);
        }
        if(getPtrNextCell(player) != NULL) player = getPtrNextCell(player);
    }while(getPtrNextCell(player) != NULL);
}
