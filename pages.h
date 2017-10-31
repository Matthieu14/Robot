#ifndef PAGES_H
#define  PAGES_h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <SDL/SDL.h>

#define NORD 0
#define EST 1
#define SUD 2
#define OUEST 3
#define TAILLE_BLOC 15

typedef struct robot{
  int orientation; /*  0=Nord, 1=Est, 2=Sud, 3=Ouest  */
  int posx;
  int posy;
  int ext;
  int pmx;
  int pmy;
  int spx;
  int spy;
}sRobot;

typedef struct graph{
  SDL_Surface *ecran;
  SDL_Surface*  mur;
  SDL_Surface*  sortie;
  SDL_Surface*  depart;
  SDL_Surface*  robot;
  SDL_Surface*  vide;

}sGraph;


/*--- Page Carte.c ---*/

char** recuperationcarte(int * pcols, int* pligs, char* nfichier);
void afficher(char** map, int ligs, int cols, sGraph infoGraph);

/*--- Page Robot.c ---*/

sRobot* initialiser_sRobot(char ** carte, int cols, int ligs);
void deplacement_robot(char ** carte, sRobot* r2d2);
void deplacement_initial(char** carte, sRobot* r2d2, int ligs, int cols,int* pcompt, sGraph infoGraph);
void tourner(char** carte, sRobot* r2d2, int orien);
int mur (char** carte, sRobot* r2d2);
int droite_rel(sRobot* r2d2);
int gauche_rel(sRobot* r2d2);
int oppose(sRobot* r2d2);
void mouvement_mur(char** carte, sRobot* r2d2);
void mouvement_ilo(char** carte, sRobot* r2d2, int ligs,int cols, int* pcompt,  sGraph infoGraph);
void fct_ilo_map(char** carte, sRobot* r2d2, int ligs,int cols, int* pcompt,  sGraph infoGraph);
int sortie(char** carte,sRobot* r2d2);

/*--- Page graph.c ---*/


void start(SDL_Surface* ecran, char** carte, int ligs, int cols, sRobot* r2d2, int* pcompt);
sGraph initialiserGraph(int ligs, int cols);
void  afficher_bloc( int i, int j, char c, sGraph infoGraph);
int rafraichit(sGraph infoGraph);
/*void deplacement_initial_graph(char** graph, sRobot* r2d2, int ligs, int* pcompt, SDL_Rect rectangle, SDL_Surface* robot, SDL_Surface* vide, int cols, SDL_Surface* ecran);
void mouvement_ilo_graph(char** graph, sRobot* r2d2, int ligs, int* pcompt, SDL_Rect rectangle, SDL_Surface* robot, SDL_Surface* vide, int cols, SDL_Surface* ecran);
void fct_ilo_map_graph(char** graph, sRobot* r2d2, int ligs, int* pcompt, SDL_Rect rectangle, SDL_Surface* robot, SDL_Surface* vide, int cols, SDL_Surface* ecran);*/




#endif
