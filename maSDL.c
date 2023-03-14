#include "SDL.h"
#include "maSDL.h"
#include "towerdefend.h"

void message(char *myTitle, char *myMessage){
        const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "ok" },
 //       { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
 //       { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        myTitle, /* .title */
        myMessage, /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        //return 1;
    }
    if (buttonid == -1) {
        SDL_Log("no selection");
    } else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }

}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //On blitte la surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void clear_surface(SDL_Surface *psurf){
        Uint32 color = SDL_MapRGB(psurf->format,0,0,0);
        SDL_FillRect(psurf,NULL, color);
}

void prepare_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination ){
    apply_surface( x, y, source, destination );
}

void efface_fenetre(SDL_Surface *psurf){
    clear_surface(psurf);
}

void maj_fenetre(SDL_Window *pWindow){
    SDL_UpdateWindowSurface(pWindow);
}

void prepareAllSpriteDuJeu(TplateauJeu jeu, int** chemin, int largeur, int hauteur, SDL_Surface **TabSprite, SDL_Surface* destination ){

    //On met de l'herbe partout
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
            prepare_sprite(i*40,j*40,TabSprite[8],destination); //herbe
        }
    }

    //on ajoute les cases du chemin en second (qui remplacent certaines cases avec de l'herbe
    for (int i=0;i<NBCOORDPARCOURS;i++){
        prepare_sprite(chemin[i][X]*40,chemin[i][Y]*40,TabSprite[10],destination); //terre
    }

    //puis les unités présentes sur le jeu
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
            if (jeu[i][j] != NULL){
                prepare_sprite(i*40,j*40,TabSprite[jeu[i][j]->nom],destination);  //remarque les sprites font 40*40 pixels

            }
        }
    }
/*
pour mémoire:
prepare_sprite(i*40,j*40,TabSprite[9],destination); // pont
prepare_sprite(i*40,j*40,TabSprite[7],destination); //eau
prepare_sprite(i*40,j*40,TabSprite[10],destination); //terre
prepare_sprite(i*40,j*40,TabSprite[8],destination); //herbe
*/
}

void dessineAttaque(SDL_Surface *surface, Tunite *attaquant, Tunite *cible ){
    int x1 = (attaquant->posX+1)*40-20;
    int y1 = (attaquant->posY+1)*40-20;
    int x2 = (cible->posX+1)*40-20;
    int y2 = (cible->posY+1)*40-20;

    /*
    //pas assez fluide
    int distX = (x2-x1)/10;
    int distY = (y2-y1)/10;

    int x = x1, y = y1;

    for (int i=0; i<10 ;i++){
        line(surface, x, y, x+distX, y+distY, 0xFF0000);
        x+=distX;  //ou x=x+distX
        y+=distY;
        SDL_Delay(150);
    }
    */
    line(surface, x1, y1, x2, y2, 0xFF0000);
    SDL_Delay(250);
}


//puts a pixel at the specifiated location
void pxl(SDL_Surface *surface, int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
    case 1:
        *p = color;
        break;

    case 2:
        *(Uint16 *)p = color;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (color >> 16) & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = color & 0xff;
        } else {
            p[0] = color & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = (color >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = color;
        break;
    }
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________
//puts a pixel at the specifiated location (clipped)

Uint8 Cpxl(SDL_Surface *surface, int x, int y, Uint32 color)
{
    if( ((x>=0) && (x<surface->w))  &&  ((y>=0) && (y<surface->h))    )
    {
        pxl(surface, x, y, color);
        return 0;
    }else{
        return 1;
    }
}



// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________
// gets the value of a pixel at the specifiated location

Uint32 getpxl(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;
    }
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


// draws a filled rectangle
void frame(SDL_Surface* surface, int x, int y, int w, int h, Uint32 color)
{
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.w = w;
    area.h = h;

    SDL_FillRect(surface, &area, color);
}

// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


// draws a filled rectangle
void cls(SDL_Surface* surface, Uint32 color)
{
    SDL_FillRect(surface, NULL, color);
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


// draws an horizontal line
void Hline(SDL_Surface* surface, int x, int y, int w, Uint32 color)
{
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.w = w;
    area.h = 1;

    SDL_FillRect(surface, &area, color);
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


// draws a vertical line
void Vline(SDL_Surface* surface, int x, int y, int h, Uint32 color)
{
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.w = 1;
    area.h = h;

    SDL_FillRect(surface, &area, color);
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________

//Draw a rectangle
void box(SDL_Surface* surface, int x, int y, int w, int h, Uint32 color)
{
  Hline(surface, x, y, w, color);
  Hline(surface, x, y + h - 1, w, color);
  Vline(surface, x, y + 1, h - 2, color);
  Vline(surface, x + w - 1, y + 1, h - 2, color);
}




// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________

//switches integers
void SwitchInt(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

void line(SDL_Surface *surface, int x1, int y1, int x2, int y2, Uint32 color)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;

  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */

    if (y1 > y2) {
      SwitchInt(&x1, &x2);
      SwitchInt(&y1, &y2);
    }

    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;

    Cpxl(surface, x, y, color);

    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
        x += xincr;
        d += aincr;
      } else
        d += bincr;

      Cpxl(surface, x, y, color);
    }

  } else {
    /* parcours par l'axe horizontal */

    if (x1 > x2) {
      SwitchInt(&x1, &x2);
      SwitchInt(&y1, &y2);
    }

    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;

    Cpxl(surface, x, y, color);

    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
        y += yincr;
        d += aincr;
      } else
        d += bincr;

      Cpxl(surface, x, y, color);
    }
  }
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


//draws a circle
void circle(SDL_Surface* surface, int cx, int cy, int rayon, int color)
{
  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
    Cpxl(surface, cx + x, cy + y, color);
    Cpxl(surface, cx + y, cy + x, color);
    Cpxl(surface, cx - x, cy + y, color);
    Cpxl(surface, cx - y, cy + x, color);
    Cpxl(surface, cx + x, cy - y, color);
    Cpxl(surface, cx + y, cy - x, color);
    Cpxl(surface, cx - x, cy - y, color);
    Cpxl(surface, cx - y, cy - x, color);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }

    x++;
  }
}


// _____________________________________________________________________________
// _____________________________________________________________________________
// _____________________________________________________________________________


//draws a filled circle
void disc(SDL_Surface *surface, int cx, int cy, int rayon, int color)
{
  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
    Hline(surface, cx - x, cy - y, 2 * x + 1, color);
    Hline(surface, cx - x, cy + y, 2 * x + 1, color);
    Hline(surface, cx - y, cy - x, 2 * y + 1, color);
    Hline(surface, cx - y, cy + x, 2 * y + 1, color);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }

    x++;
  }
}

