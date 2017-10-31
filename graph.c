#include "pages.h"




int rafraichit(sGraph infoGraph){
  SDL_Event event;
  while(SDL_PollEvent ( &event )){
    switch (event.type) {
      case SDL_QUIT:
      return 0;
      break;
    }
    SDL_Flip(infoGraph.ecran);

  }
  return 1;
}

sGraph initialiserGraph(int ligs, int cols) {
  sGraph sdl;

  if (SDL_Init (SDL_INIT_VIDEO)==-1) {
    fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE); // On quite le programme
  }
  sdl.ecran = NULL;
  sdl.ecran = SDL_SetVideoMode(cols * 15, ligs * 15, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (sdl.ecran == NULL) {
    fprintf(stderr, "Impossible de charger le mode vidéo : %s\n",
    SDL_GetError());
    exit(EXIT_FAILURE);
  }
  /*--- Titre fenetre ---*/
  SDL_WM_SetCaption("Robot", NULL);
  /*--- On met la fond de la fenetre en gris ---*/
  SDL_FillRect(sdl.ecran, NULL, 0xAAAAAA);

  sdl.mur = SDL_LoadBMP("mur.bmp");
  sdl.sortie = SDL_LoadBMP("sortie.bmp");
  SDL_SetColorKey ( sdl.sortie, SDL_SRCCOLORKEY,SDL_MapRGB( sdl.sortie->format, 0, 0, 0 ) );
  sdl.depart = SDL_LoadBMP("depart.bmp");
  sdl.robot = SDL_LoadBMP("robot.bmp");
  sdl.vide = SDL_LoadBMP("blanc.bmp");

  return sdl;
}




void  afficher_bloc( int i, int j, char c, sGraph infoGraph){
  SDL_Rect rectangle;
  rectangle.y = TAILLE_BLOC * i;
  rectangle.x = TAILLE_BLOC * j;
  switch (c) {
    case 'R':
    SDL_BlitSurface(infoGraph.robot, NULL, infoGraph.ecran, &rectangle);
    break;
    case ' ':
    SDL_BlitSurface(infoGraph.vide, NULL, infoGraph.ecran, &rectangle);
    break;
    case 'S':
    SDL_BlitSurface(infoGraph.sortie, NULL, infoGraph.ecran, &rectangle);
    break;
    case 'x':
    SDL_BlitSurface(infoGraph.mur, NULL, infoGraph.ecran, &rectangle);
    break;

  }


}
