#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "maSDL.h"
#include "towerdefend.h"
#include "listeSimple.h"

#define BINAIRE "partiebin.clb"
#define SEQUENTIEL "partieseq.cls"

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
    //(les tours ici ne sont pas li�es aux listes des unit�s de vos joueurs)
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
void ecritCheminVersleHaut  : permet d'initilaiser le tab chemin de distance cases (avec des coord x y) dans une direction, � partir d'un point x y donn�

int **chemin  : tab de coordonn�es x y du chemin
int *ichemin  : indice de la case du chemin d'o� on part
int *xdepart, int *ydepart : valeur en x y de d�part pouri la premiere case
int distance  : distance sur laquelle on va �crire des coordonn�es dans le tab chemin
int *distanceMaxRestante : securit� pour ne pas sortir de la plage d'indice de chemin
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
    printf("\nfin liste coordonn�es\n");
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
            else printf(" ");  //cad pas d'unit� sur cette case
        }
        printf("\n");
    }
}

// Les fonctions suivantes cr�ent les unit�s avec leurs stats en leur allouant un espace m�moire
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

//Retourne true si le Roi est tu�
bool tourRoiDetruite(TListePlayer playerRoi)
{
    return getPtrData(playerRoi)->pointsDeVie <= 0;
}

// Supprime toutes les unit�s de la liste player qui sont morts.
TListePlayer supprimerUnite(TListePlayer player, TplateauJeu jeu)
{
    TListePlayer newlist;
    initListe(&newlist);

    while(player != NULL) // Pour toutes les unit�s de la liste player
    {
        if(getPtrData(player)->pointsDeVie > 0) // Si l'unit� et en vie, on l'ajoute � la nouvelle liste
        {
            newlist = ajoutEnFinParPtr(newlist, getPtrData(player));
        }
        else // Sinon on la supprime du plateau.
        {
            jeu[getPtrData(player)->posX][getPtrData(player)->posY] = NULL;
        }

        player = getPtrNextCell(player);
    }

    return newlist;
}

//Cette fonction fait combattre 2 unit�s entre elles
void combat(SDL_Surface *surface, Tunite *UniteAttaquante, Tunite *UniteCible)
{
    //On v�rifie si l'unit� n'a pas d�j� attaqu� dans le tour
    if(UniteAttaquante->peutAttaquer == 1 && UniteAttaquante != NULL && UniteCible != NULL)
    {
        UniteCible->pointsDeVie -= UniteAttaquante->degats;
        UniteAttaquante->peutAttaquer = 0;

        printf("Combat: %s attaque %s et effectue %d degats. %s a maintenant %d PV.\n",
               stringUniteDuJeu(UniteAttaquante->nom),
               stringUniteDuJeu(UniteCible->nom),
               UniteAttaquante->degats,
               stringUniteDuJeu(UniteCible->nom),
               UniteCible->pointsDeVie);

        dessineAttaque(surface,UniteAttaquante,UniteCible);
    }
}

// Cette fonction cr�e une unit� random pour chaque joueur.
TplateauJeu createUnit(TListePlayer *playerRoi, TListePlayer *playerHorde, int **chemin, TplateauJeu plateau)
{
    // Choisie si une nouvelle tour spawn
    if((rand() % 100) < 2)
    {
        int positions[NBPOSITIONSTOWERS][2] = { {6, 5}, {5, 9}, {3, 3}, {5, 3}, {8, 13}, {5, 12} };
        int tourX = -1;
        int tourY = -1;

        bool positionFound = false;
        for(int i = 0; i < NBPOSITIONSTOWERS && !positionFound; i++)
        {
            if(plateau[positions[i][X]][positions[i][Y]] == NULL)
            {
                positionFound = true;
                tourX = positions[i][X];
                tourY = positions[i][Y];
            }
        }

        if(positionFound)
        {
            Tunite* newTower = NULL;
            if((rand()%100) > 50)
            {
                newTower = creeTourAir(tourX, tourY);
                *playerRoi = AjouterUnite(*playerRoi, newTower);
                printf("createUnit: spawning a new air tower.\n");
            }
            else
            {
                newTower = creeTourSol(tourX, tourY);
                *playerRoi = AjouterUnite(*playerRoi, newTower);
                printf("createUnit: spawning a new ground tower.\n");
            }

            plateau[tourX][tourY] = newTower;
        }
    }

    int spawnX = chemin[0][X];
    int spawnY = chemin[0][Y];

    // Choisis si une nouvelle unit� de la horde va apparaitre, en fonction d'une probabilit� et en v�rifiant que la case est libre.
    if((rand() % 100) < 25 && plateau[spawnX][spawnY] == NULL)
    {
        Tunite* newUnit = NULL;
        int valueUnit = rand() % 100;
        if(valueUnit < 25)
        {
            newUnit = creeGargouille(spawnX, spawnY);
            *playerHorde = AjouterUnite(*playerHorde, newUnit);
            printf("createUnit: spawning a new gargoyle.\n");
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

// Cette fonction ajoute une unit� choisit par createUnit() dans la liste de l'�quipe choisie.
// C'est � l'utilisateur de la fonction de passer la bonne liste en param�tre player (playerRoi ou playerHorde).
TListePlayer AjouterUnite(TListePlayer player, Tunite *nouvelleUnite)
{
    //On v�rifie si l'unit� est � ajouter � la fin de la liste (les membres de la horde) ou en deuxi�me position (les tours)
    if(nouvelleUnite->nom == tourAir || nouvelleUnite->nom == tourSol)
    {
        player = ajoutEnN(player, 1, *nouvelleUnite);
    }
    else
    {
        // Ajout en fin est mois rapide qu'en t�te, mais permet de g�rer les d�placement dans l'ordre d'apparition des unit�s, ce qui �vite des embouteillages.
        // Avec un ajout en t�te, il faudrait renverser la liste pour bien g�rer les d�placements.
        player = ajoutEnFin(player, *nouvelleUnite);
    }

    return player;
}

//Cette fonction permet aux unit�s de la Horde de se d�placer sur le chemin du jeu
void deplacement(TListePlayer player, int** chemin, TplateauJeu plateau)
{

    if(!listeVide(player))
    {
        //On parcourt toutes les unit�s du joueur
        TListePlayer newlist = player;
        while(newlist != NULL)
        {
            Tunite* currentUnit = getPtrData(newlist);
            int originX = currentUnit->posX;
            int originY = currentUnit->posY;

            //On parcourt les cases du chemin pour en trouver l'indice de la case de l'unit�
            int indiceCaseUnit = 0;
            while(originX != chemin[indiceCaseUnit][X] || originY != chemin[indiceCaseUnit][Y])
            {
                indiceCaseUnit ++;
            }

            //On v�rifie de combien on peut avancer l'unit� suivant sa capacit� de d�placement, si les cases sont occup�es ou non et si la fin du chemin est atteinte
            int casesMax = 0;

            while(indiceCaseUnit + casesMax + 1 < NBCOORDPARCOURS && // V�rifie si on ne va pas d�passer le bout du chemin
                    plateau[chemin[indiceCaseUnit + casesMax + 1][X]][chemin[indiceCaseUnit + casesMax + 1][Y]] == NULL && // V�rifie si la case est libre
                    casesMax + 1 <= currentUnit->vitessedeplacement) // V�rifie si on a atteint le nombre de cases maximum pour ce tour
            {
                casesMax++;
            }

            //On effectue le d�placement en changeant posX et posY dans l'unit�
            int newX = chemin[indiceCaseUnit + (casesMax)][X];
            int newY = chemin[indiceCaseUnit + (casesMax)][Y];

            currentUnit->posX = newX;
            currentUnit->posY = newY;

            // On effectue le d�placement de mani�re graphique en supprimant l'unit� de son ancienne case et en la rajoutant aux nouvelles coordonn�es.
            plateau[originX][originY] = NULL;
            plateau[newX][newY] = currentUnit;

            newlist = getPtrNextCell(newlist);
        }
    }
}

//Retourne une liste des unit�s � port�e pour l'unit� attaquante
TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante)
{
    TListePlayer l;
    initListe(&l);

    // Parcours toutes les coordonn�es de TplateauJeu
    for(int i = 0; i < LARGEURJEU; i++) // X coordinate
    {
        for(int j = 0; j < HAUTEURJEU; j++) // Y coordinate
        {
            Tunite* cible = jeu[i][j];

            if(cible != NULL)
            {
                // V�rifie si la cible est a une position attaquable (sol ou air, et pas les coordonn�es)
                if(UniteAttaquante->cibleAttaquable == cible->maposition || UniteAttaquante->cibleAttaquable == solEtAir)
                {
                    bool cibleIsEnemy = false;

                    // V�rifie si l'attaquant est dans l'�quipe du Roi et que la cible vient de la Horde.
                    if( (UniteAttaquante->nom == tourRoi || UniteAttaquante->nom == tourSol || UniteAttaquante->nom == tourAir) &&
                            (cible->nom == archer || cible->nom == chevalier || cible->nom == dragon || cible->nom == gargouille) )
                    {
                        cibleIsEnemy = true;
                    }

                    // Alternativement, V�rifie si l'attaquant est dans la Horde et que la cible vient de l'�quipe du Roi.
                    // (Les tours ne sont pas attaqu�es)
                    if( (UniteAttaquante->nom == archer || UniteAttaquante->nom == chevalier ||
                            UniteAttaquante->nom == dragon || UniteAttaquante->nom == gargouille) &&
                            cible->nom == tourRoi )
                    {
                        cibleIsEnemy = true;
                    }
                    // Cela est tr�s compliqu�, mais je n'ai pas trouv� mieux.

                    if(cibleIsEnemy)
                    {
                        int deltaX = UniteAttaquante->posX - cible->posX;
                        int deltaY = UniteAttaquante->posY - cible->posY;
                        int distanceSquared = abs(deltaX * deltaX + deltaY * deltaY);

                        // V�rifie si la cible est a port�e mais n'est pas l'attaquant lui meme
                        if(distanceSquared <= (UniteAttaquante->portee * UniteAttaquante->portee) && distanceSquared != 0 && cible->pointsDeVie > 0)
                        {
                            l = ajoutEnTeteParPtr(l, cible);
                        }
                    }
                }
            }
        }
    }

    return l;
}

// Positionne les joueurs au d�but de partie (set les spawn)
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

// R�initialise � 1 la valeur de peutAttaquer sur toutes les unit�s des deux joueurs.
void newTurnCombat(TListePlayer playerHorde, TListePlayer playerRoi)
{
    while(playerHorde != NULL)
    {
        getPtrData(playerHorde)->peutAttaquer = 1;
        playerHorde = getPtrNextCell(playerHorde);
    }

    while(playerRoi != NULL)
    {
        getPtrData(playerRoi)->peutAttaquer = 1;
        playerRoi = getPtrNextCell(playerRoi);
    }
}

// Effectue tous les combats du joueur playerAttack et retourne la version mise � jour de la liste playerEnemy
TListePlayer duringCombat(TListePlayer playerAttack, TListePlayer playerEnemy, TplateauJeu jeu, SDL_Surface *surface)
{
    while(playerAttack != NULL) // Pour toutes les unit�s de la liste playerAttack
    {
        TListePlayer targetList = quiEstAPortee(jeu, getPtrData(playerAttack));
        Tunite *weakestTarget = NULL;

        // Si la liste de cibles n'est pas vide, l'unit� la plus faible peut �tre la premi�re, on commence donc avec celle-ci
        if(!listeVide(targetList)) { weakestTarget = getPtrData(targetList); }

        while(targetList != NULL) // Trouve l'unit� la plus faible dans la liste targetList
        {
            if(getPtrData(targetList)->pointsDeVie < weakestTarget->pointsDeVie)
            {
                weakestTarget = getPtrData(targetList);
            }
            targetList = getPtrNextCell(targetList);
        }

        combat(surface, getPtrData(playerAttack), weakestTarget);

        playerAttack = getPtrNextCell(playerAttack);
    }

    playerEnemy = supprimerUnite(playerEnemy, jeu);

    return playerEnemy;
}

// Sauvegarde du jeu dans un fichier s�quentiel
void saveseq(TListePlayer playerRoi, TListePlayer playerHorde)
{
    printf("Saveseq: Started saving game to sequential file.\n");

    FILE* savefile = fopen("SEQUENTIEL", "w");
    if(savefile == NULL)
    {
        printf("ERROR - Saveseq: Failed to open partieseq.cls\n");
        return;
    }

    fprintf(savefile, "debutRoi\n");

    // Pour toutes les unit�s de la liste playerRoi
    TListePlayer newlist = playerRoi;
    while(newlist != NULL)
    {
        Tunite* currentUnit = getPtrData(newlist);
        fprintf(savefile, "%d ", currentUnit->nom); // nom est une �num�ration donc on peut l'�crire comme un entier
        fprintf(savefile, "%d ", currentUnit->pointsDeVie);
        fprintf(savefile, "%d ", currentUnit->posX);
        fprintf(savefile, "%d ", currentUnit->posY);
        fprintf(savefile, "\n");

        newlist = getPtrNextCell(newlist);
    }
    fprintf(savefile, "finRoi\n");

    fprintf(savefile, "debutHorde\n");

    // Pour toutes les unit�s de la liste playerHorde
    newlist = playerHorde;
    while(newlist != NULL)
    {
        Tunite* currentUnit = getPtrData(newlist);
        fprintf(savefile, "%d ", currentUnit->nom);
        fprintf(savefile, "%d ", currentUnit->pointsDeVie);
        fprintf(savefile, "%d ", currentUnit->posX);
        fprintf(savefile, "%d ", currentUnit->posY);
        fprintf(savefile, "\n");

        newlist = getPtrNextCell(newlist);
    }
    fprintf(savefile, "finHorde\n");

    fclose(savefile);

    printf("Saveseq: Finished saving game to sequential file.\n");
}

// Chargement du jeu depuis un fichier s�quentiel
void loadseq(TListePlayer* playerRoi, TListePlayer* playerHorde, TplateauJeu jeu)
{
    printf("Loadseq: Started loading game from sequential file.\n");

    FILE* savefile = fopen("SEQUENTIEL", "r");
    if(savefile == NULL)
    {
        printf("ERROR - Loadseq: Failed to open partieseq.cls.\n");
        return;
    }

    // R�initialise les listes des joueurs
    *playerRoi = supprimeListe(*playerRoi);
    *playerHorde = supprimeListe(*playerHorde);


    // R�initialise le plateau
    for(int i = 0; i < LARGEURJEU; i++)
    {
        for(int j = 0; j < HAUTEURJEU; j++)
        {
            jeu[i][j] = NULL;
        }
    }

    char buffer[255];

    // D�but du chargement de la liste playerRoi
    fscanf(savefile, "%s", buffer);
    if(strcmp(buffer, "debutRoi") != 0) // Si le fichier ne commence pas par "debutRoi", alors il est incorrect
    {
        printf("ERROR - Loadseq: Sequential file contains incorrect data.\n");
        return;
    }

    for(int i =0; i < 2048; i++) // 2048 est une limite arbitraire pour �viter de cr�er une boucle infinie
    {
        Tunite* currentUnit = NULL;
        int nom, pv, x, y;

        fscanf(savefile, "%s", buffer);
        if(strcmp(buffer, "finRoi") != 0) // Si on lit "finRoi", la section de la liste du roi est termin�e, donc on break pour sortir de la liste.
            nom = atoi(buffer);
        else
            break;

        fscanf(savefile, "%d", &pv);
        fscanf(savefile, "%d", &x);
        fscanf(savefile, "%d", &y);

        switch(nom)
        {
        case tourRoi:
            currentUnit = creeTourRoi(x, y);
            currentUnit->pointsDeVie = pv;
            break;
        case tourAir:
            currentUnit = creeTourAir(x, y);
            break;
        case tourSol:
            currentUnit = creeTourSol(x, y);
            break;
        default:
            break;
        } // Les tours air et sol ne se font pas attaquer, il est donc inutile de charger leurs points de vie.

        *playerRoi = AjouterUnite(*playerRoi, currentUnit);
    }

    // D�but du chargement de la liste playerHorde
    fscanf(savefile, "%s", buffer);
    if(strcmp(buffer, "debutHorde") != 0) // Si la section suivante ne commence pas par "debutHorde", alors elle est incorrecte
    {
        printf("ERROR - Loadseq: Sequential file contains incorrect data.\n");
        return;
    }

    for(int i =0; i < 2048; i++) // 2048 est une limite arbitraire pour �viter de cr�er une boucle infinie
    {
        Tunite* currentUnit = NULL;
        int nom, pv, x, y;

        fscanf(savefile, "%s", buffer);
        if(strcmp(buffer, "finHorde") != 0) // Si on lit "finHorde", la section de la liste du roi est termin�e, donc on break pour sortir de la liste.
            nom = atoi(buffer);
        else
            break;

        fscanf(savefile, "%d", &pv);
        fscanf(savefile, "%d", &x);
        fscanf(savefile, "%d", &y);

        switch(nom)
        {
        case dragon:
            currentUnit = creeDragon(x, y);
            currentUnit->pointsDeVie = pv;
            break;
        case gargouille:
            currentUnit = creeGargouille(x, y);
            currentUnit->pointsDeVie = pv;
            break;
        case archer:
            currentUnit = creeArcher(x, y);
            currentUnit->pointsDeVie = pv;
            break;
        case chevalier:
            currentUnit = creeChevalier(x, y);
            currentUnit->pointsDeVie = pv;
            break;
        default:
            break;
        }
        *playerHorde = AjouterUnite(*playerHorde, currentUnit);
    }

    fclose(savefile);

    jeu = PositionnePlayerOnPlateau(*playerRoi, jeu);
    jeu = PositionnePlayerOnPlateau(*playerHorde, jeu);

    printf("Loadseq: Finished loading game from sequential file.\n");
}

// Sauvegarde du jeu dans un fichier binaire en transformant les listes en tableaux, qu'on �crit dans le fichier.
void savebin(TListePlayer playerRoi, TListePlayer playerHorde)
{
    printf("Savebin: Started saving game to binary file.\n");

    FILE* savefile = fopen("BINAIRE", "wb"); // On ouvre le fichier de sauvegarde en mode �criture binaire
    if(savefile == NULL)
    {
        printf("ERROR - Savebin: Failed to open partiebin.clb.\n");
        return;
    }

    long sizeRoi = getSizeBytes(playerRoi);
    long sizeHorde = getSizeBytes(playerHorde);

    int lenghRoi;
    int lengthHorde;

    Tunite* arrRoi;
    Tunite* arrHorde;

    arrRoi = listToArray(playerRoi, &lenghRoi);
    arrHorde = listToArray(playerHorde, &lengthHorde);

    // On �crit les donn�es dans l'ordre: tailleTableauRoi, longueurTableauRoi, TableauRoi, tailleTableauHorde, longueurTableauHorde, TableauHorde.

    fwrite(&sizeRoi, sizeof(long), 1, savefile); // �crit la taille du tableau conenant la liste du roi
    fwrite(&lenghRoi, sizeof(int), 1, savefile); // �crit la longueur du tableau conenant la liste du roi
    fwrite(arrRoi, sizeRoi, 1, savefile); // �crit le tableau contenant la liste du roi

    fwrite(&sizeHorde, sizeof(long), 1, savefile); // �crit la taille du tableau conenant la liste de la horde
    fwrite(&lengthHorde, sizeof(int), 1, savefile); // �crit la longueur du tableau conenant la liste de la horde
    fwrite(arrHorde, sizeHorde, 1, savefile); // �crit le tableau contenant la liste de la horde

    fclose(savefile);

    printf("Savebin: Finished saving game to binary file.\n");
}

// Chargement du jeu depuis un fichier binaire, en convertissant les tableaux stock�s dans le fichier en listes.
void loadbin(TListePlayer* playerRoi, TListePlayer* playerHorde, TplateauJeu jeu)
{
    printf("Loadbin: Started loading game from binary file.\n");

    FILE* savefile = fopen("BINAIRE", "rb");
    if(savefile == NULL)
    {
        printf("ERROR - Loadbin: Failed to open partiebin.clb.\n");
        return;
    }

    long sizeRoi;
    long sizeHorde;

    int lengthRoi;
    int lengthHorde;

    // R�initialise le plateau
    for(int i = 0; i < LARGEURJEU; i++)
    {
        for(int j = 0; j < HAUTEURJEU; j++)
        {
            jeu[i][j] = NULL;
        }
    }

    // Lis les donn�es dans le m�me ordre qu'on les a �crit.

    fread(&sizeRoi, sizeof(long), 1, savefile);
    fread(&lengthRoi, sizeof(int), 1, savefile);
    Tunite* arrRoi = malloc(sizeRoi);
    fread(arrRoi, sizeRoi, 1, savefile);

    fread(&sizeHorde, sizeof(long), 1, savefile);
    fread(&lengthHorde, sizeof(int), 1, savefile);
    Tunite* arrHorde = malloc(sizeHorde);
    fread(arrHorde, sizeHorde, 1, savefile);

    fclose(savefile);

    // Restaure la valeur des listes des joueurs
    *playerRoi = arrayToList(arrRoi, lengthRoi);
    *playerHorde = arrayToList(arrHorde, lengthHorde);

    // Actualise le plateau
    jeu = PositionnePlayerOnPlateau(*playerRoi, jeu);
    jeu = PositionnePlayerOnPlateau(*playerHorde, jeu);

    printf("Loadbin: Finished loading game from binary file.\n");
}
