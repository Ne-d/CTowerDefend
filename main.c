//NOM pr�nom �tudiant 1 : CHEVALIER Jean-Michel
//NOM pr�nom �tudiant 2 : DENIS Baptiste

#include "SDL.h"
#include "maSDL.h"    //biblioth�que avec des fonctions d'affichage utilisant la SDL
#include "towerdefend.h"
#include "listeSimple.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BINAIRE "partiebin.clb"
#define SEQUENTIEL "partieseq.cls"


/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
                  "Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes",
                  SDL_WINDOWPOS_UNDEFINED,
                  SDL_WINDOWPOS_UNDEFINED,
                  LARGEURJEU*40,
                  HAUTEURJEU*40,
                  SDL_WINDOW_SHOWN
              );

    //SDL_Renderer * renderer = SDL_CreateRenderer(pWindow, -1, 0);  //non utilis�, pour m�moire

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'�cran
    SDL_Surface* pSpriteTourSol = SDL_LoadBMP("./data/TourSol.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourAir = SDL_LoadBMP("./data/TourAir.bmp");  //indice 1 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi = SDL_LoadBMP("./data/TourRoi.bmp"); //indice 2
    SDL_Surface* pSpriteArcher = SDL_LoadBMP("./data/Archer.bmp"); //indice 3
    SDL_Surface* pSpriteChevalier = SDL_LoadBMP("./data/Chevalier.bmp"); //indice 4
    SDL_Surface* pSpriteDragon = SDL_LoadBMP("./data/Dragon.bmp"); //indice 5
    SDL_Surface* pSpriteGargouille = SDL_LoadBMP("./data/Gargouille.bmp"); //indice 6
    SDL_Surface* pSpriteEau = SDL_LoadBMP("./data/Eau.bmp"); //indice 7  Ne figure pas dans l'enum TuniteDuJeu
    SDL_Surface* pSpriteHerbe = SDL_LoadBMP("./data/Herbe.bmp"); //indice 8 idem
    SDL_Surface* pSpritePont = SDL_LoadBMP("./data/Pont.bmp"); //indice 9 idem
    SDL_Surface* pSpriteTerre = SDL_LoadBMP("./data/Terre.bmp"); //indice 10 idem

    // ASTUCE : on stocke le sprite d'une unit� � l'indice de son nom dans le type enum TuniteDuJeu, dans le tableau TabSprite
    // SAUF pour l'Eau, l''herbe et le pont qui apparaitront en l absence d'unit� (NULL dans le plateau) et en foction de certains indices x,y d�finissant le chemin central
    SDL_Surface* TabSprite[11]= {pSpriteTourSol,pSpriteTourAir,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};

    int** tabParcours=initChemin();  //tabParcours est un tableau de NBCOORDPARCOURS cases, chacune contenant un tableau � 2 cases (indice 0 pour X, indice 1 pour Y)

    if ( pSpriteTourSol )  //si le premier sprite a bien �t� charg�, on suppose que les autres aussi
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);

        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);


        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */

        printf("Begin initialization.\n");

        TListePlayer playerRoi;
        TListePlayer playerHorde;

        initListe(&playerRoi);
        initListe(&playerHorde);

        // Initialise le g�n�rateur de nombres pseudo-al�atoires
        srand(time(NULL));

        // Ajoute le roi � la liste de son �quipe et au plateau de jeu
        playerRoi = AjouterUnite(playerRoi, creeTourRoi(4, 1));
        jeu = PositionnePlayerOnPlateau(playerRoi, jeu);

        printf("End initialization.\n\n");


        /* FIN de vos variables                                               */
        /**********************************************************************/


        // boucle principale du jeu
        int cont = 1;
        while ( !tourRoiDetruite(playerRoi) && cont == 1 )   // La boucle se termine quand le roi meurt
        {
            SDL_PumpEvents(); //do events
            efface_fenetre(pWinSurf);
            prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);

            /***********************************************************************/
            /*                                                                     */
            /*                                                                     */
            //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU

            printf("New turn starts.\n");
            newTurnCombat(playerHorde,playerRoi);

            jeu = createUnit(&playerRoi, &playerHorde, tabParcours, jeu);

            deplacement(playerHorde, tabParcours, jeu);

            playerHorde = duringCombat(playerRoi, playerHorde, jeu, pWinSurf);
            playerRoi = duringCombat(playerHorde, playerRoi, jeu, pWinSurf);

            if(playerRoi != NULL)
            {
                printf("Vie du roi: %d\n", getPtrData(playerRoi)->pointsDeVie);
            }
            else
            {
                printf("\nGame Over: Defaite du Roi, victoire de la Horde.\n");
                return 0;
            }

            /*                                                                     */
            /*                                                                     */
            // FIN DE VOS APPELS
            /***********************************************************************/
            //affichage du jeu � chaque tour

            maj_fenetre(pWindow);
            SDL_Delay(150);  // Valeur du d�lai � modifier �ventuellement


            //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES
            const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
            if ( pKeyStates[SDL_SCANCODE_V] )
            {
                loadseq(&playerRoi, &playerHorde, jeu);

                //Ne pas modifiez les 4 lignes ci-dessous
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(300);
            }
            if ( pKeyStates[SDL_SCANCODE_C] )
            {
                loadbin(&playerRoi, &playerHorde, jeu);

                //Ne pas modifiez les 4 lignes ci-dessous
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(300);
            }
            if ( pKeyStates[SDL_SCANCODE_D] )
            {
                saveseq(playerRoi, playerHorde);

                //Ne pas modifiez les 4 lignes ci-dessous
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(300);
            }
            if ( pKeyStates[SDL_SCANCODE_S] )
            {
                savebin(playerRoi, playerHorde);

                //Ne pas modifiez les 4 lignes ci-dessous
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(300);
            }
            if ( pKeyStates[SDL_SCANCODE_ESCAPE] )
            {
                cont = 0;  //sortie de la boucle
            }

            printf("End of the turn.\n\n");

        }
        //fin boucle du jeu

        SDL_FreeSurface(pSpriteTourSol); // Lib�ration de la ressource occup�e par le sprite
        SDL_FreeSurface(pSpriteTourAir);
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteEau);
        SDL_FreeSurface(pSpriteHerbe);
        SDL_FreeSurface(pSpritePont);
        SDL_FreeSurface(pWinSurf);
    }
    else
    {
        fprintf(stdout,"�chec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}
