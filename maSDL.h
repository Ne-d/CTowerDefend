//"surcouche partielle" de la SDL pour les affichages liés au jeu2048


#include "towerdefend.h"
#ifndef MASDL_H_INCLUDED
#define MASDL_H_INCLUDED




void message(char *myTitle, char *myMessage);


//void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
//void clear_surface(SDL_Surface *psurf);

void prepare_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination );
void efface_fenetre(SDL_Surface *psurf);
void maj_fenetre(SDL_Window *pWindow);

void prepareAllSpriteDuJeu(TplateauJeu jeu, int** chemin, int largeur, int hauteur, SDL_Surface **TabSprite, SDL_Surface* destination );
void dessineAttaque(SDL_Surface *surface, Tunite *attaquant, Tunite *cible );



// propre à la sdl

void pxl(SDL_Surface *surface, int x, int y, Uint32 color);
// Sets the pixel at (x, y) in the specified surface.

Uint32 getpxl(SDL_Surface *surface, int x, int y);
// Returns the value of a pixel at (x,y) from the specified surface.

void frame(SDL_Surface* surface, int x, int y, int w, int h, Uint32 color);
// Draws a colored filled box at (x, y) with specified width and height.

void cls(SDL_Surface* surface, Uint32 color);
// Fill the entire surface with specified color

void Hline(SDL_Surface* surface, int x, int y, int w, Uint32 color);
// Draws and colored horizontal line at (x, y) with specified width.

void Vline(SDL_Surface* surface, int x, int y, int h, Uint32 color);
// Draws and colored horizontal line at (x, y) with specified height.

Uint8 Cpxl(SDL_Surface *surface, int x, int y, Uint32 color);
// Checks wether the pixel is in the surface before calling pxl function.

void box(SDL_Surface* surface, int x, int y, int w, int h, Uint32 color);
// Draws a colored square or a rectangle at (x, y) with specified width and
// height.

void line(SDL_Surface *surface, int x1, int y1, int x2, int y2, Uint32 color);
// Draws a colored line from A(x, y) to B(x, y).

void circle(SDL_Surface* surface, int cx, int cy, int rayon, int color);
// Draws a colored circle with center at (x, y) and with the specified radius.

void disc(SDL_Surface *surface, int cx, int cy, int rayon, int color);
// Draws a colored filled circle with center at (x, y) and with the specified
// radius.

#endif // MASDL_H_INCLUDED



/*
exemples d'utilisation :

pxl(ecran, 10, 10, color); // pixel de la couleur color en 10, 10 sur ecran.

getpxl(ecran, 10, 10); // renvoie l'Uint32 correspondant aux couleurs du pixel en 10, 10 sur ecran.

frame(ecran, 10, 10, 20, 30, color); // rectangle remplit de largeur 20 et hauteur 30 en 10, 10 sur ecran et de couleur color.

cls(ecran, 0); // remplit ecran de noir ( = efface l'écran).

Hline(ecran, 10, 10, 50, color); // ligne horizontale de 50 pxl commençant en 10, 10 de couleur color.

Vline(ecran, 10, 10, 50, color); // ligne verticale de 50 pxl commençant en 10, 10 de couleur color.

Cpxl(ecran, 10, 16, color); // verifie que les coordonnées sont dans ecran avant d'appeler pxl(ecran, 10, 16, color) ( = clipping).

box(ecran, 10, 10, 50, 20, color); // rectangle vide de couleur color en 10, 10 de dimensions 50, 20.

line(ecran, 0, 0, 10, 10, 0xFF0000); ligne  rouge entredeux pts de coordonnées (0, 0) et (10, 10) inclus.

circle(ecran, 10, 10, 5, color); cercle vide en 10, 10 de rayon 5 et de couleur color.

disc(ecran, 10, 10, 5, color); cercle plein en 10, 10 de rayon 5 et de couleur color.
*/
