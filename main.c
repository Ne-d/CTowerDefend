//NOM prénom étudiant 1 : CHEVALIER Jean-Michel
//NOM prénom étudiant 2 : DENIS Baptiste

#include "SDL.h"
#include "maSDL.h"    //bibliothèque avec des fonctions d'affichage utilisant la SDL
#include "towerdefend.h"
#include "testListeSimple.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



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

    //SDL_Renderer * renderer = SDL_CreateRenderer(pWindow, -1, 0);  //non utilisé, pour mémoire

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'écran
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

    // ASTUCE : on stocke le sprite d'une unité à l'indice de son nom dans le type enum TuniteDuJeu, dans le tableau TabSprite
    // SAUF pour l'Eau, l''herbe et le pont qui apparaitront en l absence d'unité (NULL dans le plateau) et en foction de certains indices x,y définissant le chemin central
    SDL_Surface* TabSprite[11]={pSpriteTourSol,pSpriteTourAir,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};

    int** tabParcours=initChemin();  //tabParcours est un tableau de NBCOORDPARCOURS cases, chacune contenant un tableau à 2 cases (indice 0 pour X, indice 1 pour Y)

    if ( pSpriteTourSol )  //si le premier sprite a bien été chargé, on suppose que les autres aussi
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);

        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);


        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */

           TListePlayer playerRoi;
           TListePlayer playerHorde;

           initListe(&playerRoi);
           initListe(&playerHorde);

        /* FIN de vos variables                                               */
        /**********************************************************************/


        // boucle principale du jeu
        int cont = 1;
        while ( cont != 0 ){   //VOUS DEVEZ GERER (DETECTER) LA FIN DU JEU -> tourRoiDetruite
                SDL_PumpEvents(); //do events
                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);

                /***********************************************************************/
                /*                                                                     */
                /*                                                                     */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU

                // Initialise le générateur de nombres pseudo-aléatoires
                srand(time(NULL));

                /* dans votre fonction "combat" que vous appelerez ici, dans son code utiliser dessineAttaque

                //exemple d'appel de dessineAttaque (factice car les unités n'appartiennent pas ici à aucune liste d'unité (ni à la horde ni au Roi)
                // c'est juste pour la démo, a supprimer donc
                */

                /*
                if (unique % 10 == 0) {
                         printf("dessine Attaque %d\n", unique);
                         dessineAttaque(pWinSurf, creeTourAir(4,15),creeDragon(5,17));
                         dessineAttaque(pWinSurf, creeDragon(5,17),creeTourRoi(4,1));
                         unique++;
                } else printf("dessine Attaque %d\n", unique);
                unique++;
                */

                // utiliser dessineAttaque dans votre fonction de combat va vous obliger à ajouter un argument lié à la SDL
                // -> SDL_Surface *surface
                // regarder le prototype de dessineAttaque dans maSDL.c pour (mieux) comprendre

                /*                                                                     */
                /*                                                                     */
                // FIN DE VOS APPELS
                /***********************************************************************/
                //affichage du jeu à chaque tour

                maj_fenetre(pWindow);
                SDL_Delay(150);  //valeur du délai à modifier éventuellement


                //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES
                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                if ( pKeyStates[SDL_SCANCODE_V] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_C] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur C */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_D] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_S] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appyue sur S */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){
                        cont = 0;  //sortie de la boucle
                }

        }
        //fin boucle du jeu

        SDL_FreeSurface(pSpriteTourSol); // Libération de la ressource occupée par le sprite
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
        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}
