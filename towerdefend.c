#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "maSDL.h"
#include "towerdefend.h"
#include "listeSimple.h"
#define BINAIRE "partiebin.clb"
#define SEQUENTIEL "partieseq.cls"


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
    return getPtrData(playerRoi)->pointsDeVie <= 0;
}

// Supprime toutes les unités de la liste player qui sont morts.
// A Test
TListePlayer supprimerUnite(TListePlayer player, TplateauJeu jeu)
{
    TListePlayer newlist;
    initListe(&newlist);

    while(player != NULL) // Pour toutes les unités de la liste player
    {
        if(getPtrData(player)->pointsDeVie > 0) // Si l'unité et en vie, on l'ajoute à la nouvelle liste
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

//Cette fonction fait combattre 2 unités entre elles
//A test
void combat(SDL_Surface *surface, Tunite *UniteAttaquante, Tunite *UniteCible)
{
    //On vérifie si l'unité n'a pas déjà attaqué dans le tour
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

// This function creates a unit randomly for each player.
// TODO: Cleanup
TplateauJeu createUnit(TListePlayer *playerRoi, TListePlayer *playerHorde, int **chemin, TplateauJeu plateau)
{
    // Chooses if a new tower will spawn
    if((rand() % 100) < 5) // TODO: Change this value, this will never spawn towers
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

    // Choisis si une nouvelle unité de la horde va apparaitre, en fonction d'une probabilité et en vérifiant que la case est libre.
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

//A test
// Cette fonction ajoute une unité choisit par createUnit() dans la liste de l'équipe choisie.
// C'est à l'utilisateur de la fonction de passer la bonne liste en paramètre player (playerRoi ou playerHorde).
TListePlayer AjouterUnite(TListePlayer player, Tunite *nouvelleUnite)
{
    //On vérifie si l'unité est à ajouter à la fin de la liste (les membres de la horde) ou en deuxième position (les tours)
    if(nouvelleUnite->nom == tourAir || nouvelleUnite->nom == tourSol)
    {
        player = ajoutEnN(player, 1, *nouvelleUnite);
    }
    else
    {
        // Ajout en fin est mois rapide qu'en tête, mais permet de gérer les déplacement dans l'ordre d'apparition des unités, ce qui évite des embouteillages.
        // Avec un ajout en tête, il faudrait renverser la liste pour bien gérer les déplacements.
        player = ajoutEnFin(player, *nouvelleUnite);
    }

    return player;
}

//Cette fonction permet aux unités de la Horde de se déplacer sur le chemin du jeu
// TODO: Cleanup
void deplacement(TListePlayer player, int** chemin, TplateauJeu plateau)
{

    if(!listeVide(player))
    {
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
}

// TODO: This is untested.
//Retourne une liste des unités à portée pour l'unité attaquante
TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante)
{
    TListePlayer l;
    initListe(&l);

    // Loop through all coordinates of the TplateauJeu
    // TODO: This could be made more efficient by only looking at a square around the attacking unit.
    for(int i = 0; i < LARGEURJEU; i++) // X coordinate
    {
        for(int j = 0; j < HAUTEURJEU; j++) // Y coordinate
        {
            Tunite* cible = jeu[i][j];

            if(cible != NULL)
            {
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

// Réinitialise à 1 la valeur de peutAttaquer sur toutes les unités des deux joueurs.
// A tester
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

// Effectue tous les combats du joueur playerAttack et retourne la version mise à jour de la liste playerEnemy
TListePlayer duringCombat(TListePlayer playerAttack, TListePlayer playerEnemy, TplateauJeu jeu, SDL_Surface *surface)
{
    while(playerAttack != NULL) // Pour toutes les unités de la liste playerAttack
    {
        TListePlayer targetList = quiEstAPortee(jeu, getPtrData(playerAttack));
        Tunite *weakestTarget = NULL;

        // Si la liste de cibles n'est pas vide, l'unité la plus faible peut être la première, on commence donc avec celle-ci
        if(!listeVide(targetList)) { weakestTarget = getPtrData(targetList); }

        while(targetList != NULL) // Trouve l'unité la plus faible dans la liste targetList
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

void saveseq(TListePlayer roi, TListePlayer horde)
{
    FILE* file = fopen("partieseq.cls", "w"); // Ouvrir le fichier "partieseq.cls" en écriture "w"
    if (file == NULL)
        return;

    TListePlayer temp;
    fprintf(file, "roi\n"); // fprintf ça écrit dans le fichier, ça s'utilise comme printf
    for (temp = roi; !listeVide(temp); temp = getPtrNextCell(temp))
    {
        Tunite* unite = getPtrData(temp);
        fprintf(file, "%d ", unite->nom);
        fprintf(file, "%d ", unite->posX);
        fprintf(file, "%d ", unite->posY);
        fprintf(file, "%d ", unite->pointsDeVie);
        fprintf(file, "\n");
    }
    fprintf(file, "fin_roi\n");

    // Horde
    fprintf(file, "horde\n");
    for (temp = horde; !listeVide(temp); temp = getPtrNextCell(temp))
    {
        Tunite* unite = getPtrData(temp);
        fprintf(file, "%d ", unite->nom);
        fprintf(file, "%d ", unite->posX);
        fprintf(file, "%d ", unite->posY);
        fprintf(file, "%d ", unite->pointsDeVie);
        fprintf(file, "\n");
    }
    fprintf(file, "fin_horde\n");

    fclose(file); // Oublie pas de fermer le fichier sinon tu vas te faire taper
    printf("Le jeu a bien ete sauvegarde via le systeme sequentiel\n");
}

void loadseq(TListePlayer* roi, TListePlayer* horde) // J'ai mis des pointeurs pour pouvoir les modifier dans la fonction
{
    FILE* file = fopen("partieseq.cls", "r");
    if (file == NULL)
        return;

    //Roi
    char roiStr[100];
    fscanf(file, "%s", roiStr); // fscanf ça lit dans le fichier jusqu'au prochain espace ou \n, ça s'utilise comme scanf
    if (strcmp(roiStr, "roi") != 0)
        return;

    *roi = deleteList(*roi); // Supprime la liste pour partir sur un truc neuf

    int iters = 0; // Pour être sûr de pas faire de boucle infinie
    while (iters < 1024)
    {
        iters++;

        Tunite* unite = NULL;
        int nom;
        int x, y, pointsDeVie;

        fscanf(file, "%s", roiStr);
        if (strcmp(roiStr, "fin_roi") != 0)
            nom = atoi(roiStr);
        else
            break;

        fscanf(file, "%d", &x);
        fscanf(file, "%d", &y);
        fscanf(file, "%d", &pointsDeVie);

        switch (nom)
        {
        case tourRoi:
            unite = creeTourRoi(x, y);
            unite->pointsDeVie = pointsDeVie; //Uniquement le roi perd des PV
            break;
        case tourAir:
            unite = creeTourAir(x, y);
            break;
        case tourSol:
            unite = creeTourSol(x, y);
            break;
        default:
            break;
        }

        *roi = AjouterUnite(*roi, unite);
    }

    //Horde
    char hordeStr[100];
    fscanf(file, "%s", hordeStr);
    if (strcmp(hordeStr, "horde") != 0)
        return;

    *horde = deleteList(*horde);

    iters = 0;
    while (iters < 1024)
    {
        iters++;

        Tunite* unite = NULL;
        int nom;
        int x, y, pointsDeVie;

        fscanf(file, "%s", hordeStr);
        if (strcmp(hordeStr, "fin_horde") != 0)
            nom = atoi(hordeStr);
        else
            break;

        fscanf(file, "%d", &x);
        fscanf(file, "%d", &y);
        fscanf(file, "%d", &pointsDeVie);

        switch (nom)
        {
        case archer:
            unite = creeArcher(x, y);
            unite->pointsDeVie = pointsDeVie;
            break;
        case chevalier:
            unite = creeChevalier(x, y);
            unite->pointsDeVie = pointsDeVie;
            break;
        case dragon:
            unite = creeDragon(x, y);
            unite->pointsDeVie = pointsDeVie;
            break;
        case gargouille:
            unite = creeGargouille(x, y);
            unite->pointsDeVie = pointsDeVie;
            break;
        default:
            break;
        }

        *horde = AjouterUnite(*horde, unite);
    }

    fclose(file);
    printf("Fin du chargement\n");
}
