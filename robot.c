#include "pages.h"


sRobot* initialiser_sRobot(char** carte, int cols, int ligs){
  int i;
  int j;
  sRobot* r2d2=(sRobot*)malloc(sizeof(sRobot));

  for ( j = 0; j < ligs; j++) {  /*--- Récuperation du point de départ du Robot ---*/
    for ( i = 0; i < cols; i++) {
      if (carte[j][i]=='D') {
        r2d2->posx=i;
        r2d2->posy=j;
      }
    }
  }
  r2d2->ext=0; /*--- On met la sortie a 0 pour faire avancer le programme ---*/
  r2d2->orientation=EST;//rand()%3;
  //  while (r2d2->orientation==1) {
  //    r2d2->orientation=rand()%3;
  //  } /*--- On désigne l'orientation de départ du robot ---*/

  return r2d2;
}

void deplacement_initial(char** carte, sRobot* r2d2, int ligs, int cols,int* pcompt, sGraph infoGraph){
  //On vérifie que la sortie n'est pas a coté de lui, sinon il continue la fonction
  if (sortie(carte, r2d2)==1) {
    r2d2->ext=1;
  }
  else {
    switch (r2d2->orientation){
      //Pour chaque orientation on avance jusqu'à temps de trouver le premier mur
      //On affiche la carte à chaque déplacement et on incrémente le compteur d'étapes
      case NORD:
      while(!mur(carte, r2d2)){
        deplacement_robot(carte, r2d2);
        carte[r2d2->posy+1][r2d2->posx]=' ';
        carte[r2d2->posy][r2d2->posx]='R';
        usleep(10000);
        system("clear");
        afficher(carte, ligs, cols, infoGraph);
        pcompt++;
      }
      r2d2->pmx=r2d2->posx;
      r2d2->pmy=r2d2->posy;
      tourner(carte, r2d2, OUEST);
      break;
      case EST:
      while(!mur(carte, r2d2)){
        deplacement_robot(carte, r2d2);
        carte[r2d2->posy][r2d2->posx-1]=' ';
        carte[r2d2->posy][r2d2->posx]='R';
        usleep(10000);
        system("clear");
        afficher(carte, ligs, cols, infoGraph);
        pcompt++;
      }
      r2d2->pmx=r2d2->posx;
      r2d2->pmy=r2d2->posy;
      tourner(carte, r2d2, NORD);
      break;
      case SUD:
      while(!mur(carte, r2d2)){
        deplacement_robot(carte, r2d2);
        carte[r2d2->posy-1][r2d2->posx]=' ';
        carte[r2d2->posy][r2d2->posx]='R';
        usleep(10000);
        system("clear");
        afficher(carte, ligs, cols, infoGraph);
        pcompt++;
      }
      r2d2->pmx=r2d2->posx;
      r2d2->pmy=r2d2->posy;
      tourner(carte, r2d2, EST);
      break;
      case OUEST:
      while(! mur(carte, r2d2)){
        deplacement_robot(carte, r2d2);
        carte[r2d2->posy][r2d2->posx+1]=' ';
        carte[r2d2->posy][r2d2->posx]='R';
        usleep(10000);
        system("clear");
        afficher(carte, ligs, cols, infoGraph);
        pcompt++;
      }
      r2d2->pmx=r2d2->posx;
      r2d2->pmy=r2d2->posy;
      tourner(carte, r2d2, SUD);
      break;
    }
  }
}

void deplacement_robot(char** carte, sRobot* r2d2){
  //On vérifie que la sortie n'est pas a coté de lui, sinon il continue la fonction
  if (sortie(carte, r2d2)) {
    r2d2->ext=1;
  }
  else {
    carte[r2d2->posy][r2d2->posx]=' ';  //On remet la case du robot en temps que libre
    switch (r2d2->orientation) {        //En fonction de l'orientation on déplace le robot dans une position
      case NORD:
      r2d2->posy--;
      break;
      case EST:
      r2d2->posx++;
      break;
      case SUD:
      r2d2->posy++;
      break;
      case OUEST:
      r2d2->posx--;
      break;

    }
    carte[r2d2->posy][r2d2->posx]='R'; //On affiche le robot à sa nouvelle position
  }
}

void tourner(char** carte, sRobot* r2d2, int orien){
  r2d2->orientation=orien; //On affecte la nouvelle orientation avec celle demandée
}

int mur (char** carte, sRobot* r2d2){
  int tempx, tempy;
  switch (r2d2->orientation) {
    case NORD:
    tempy=r2d2->posy-1; //Dans les variables temporaires on affect les coordonées suivante du robot
    tempx=r2d2->posx;
    break;
    case EST:
    tempx=r2d2->posx+1;
    tempy=r2d2->posy;
    break;
    case SUD:
    tempy=r2d2->posy+1;
    tempx=r2d2->posx;
    break;
    case OUEST:
    tempx=r2d2->posx-1;
    tempy=r2d2->posy;
    break;
  }
  if (carte[tempy][tempx]=='x') { //si il y a un mur au coordonnées possible du robot on renvoie 1, sinon 0
    return 1;
  }
  else return 0;
}

int droite_rel(sRobot* r2d2){

  switch(r2d2->orientation){ //On cherche juste la droite réelle du robot

      case NORD:
      return EST;
      break;
      case EST:
      return SUD;
      break;
      case SUD:
      return OUEST;
      break;
      case OUEST:
      return NORD;
      break;
    }
  return 0;
}

int gauche_rel(sRobot* r2d2){

  switch(r2d2->orientation){ //On cherche juste la gauche réelle du robot

      case NORD:
      return OUEST;
      break;
      case EST:
      return NORD;
      break;
      case SUD:
      return EST;
      break;
      case OUEST:
      return SUD;
      break;
    }
  return 0;
}

int oppose(sRobot* r2d2){

  switch(r2d2->orientation){ //On cherche juste la gauche réelle du robot

      case NORD:
      return SUD;
      break;
      case EST:
      return OUEST;
      break;
      case SUD:
      return NORD;
      break;
      case OUEST:
      return EST;
      break;
    }
  return 0;

}

void mouvement_mur(char** carte, sRobot* r2d2){

  tourner(carte, r2d2, droite_rel(r2d2));
  if ((mur(carte, r2d2))==0) {
    deplacement_robot(carte, r2d2);
  }
  else{ tourner(carte, r2d2, gauche_rel(r2d2));
    if ((mur(carte, r2d2))==0) {
      deplacement_robot(carte, r2d2);
    }
    else {tourner(carte, r2d2, gauche_rel(r2d2));
      if ((mur(carte, r2d2))==0) {
        deplacement_robot(carte, r2d2);
      }
    }
  }
}

void mouvement_ilo(char** carte, sRobot* r2d2, int ligs,int cols, int* pcompt,  sGraph infoGraph){
  int i=0;
  while (r2d2->ext==0) {
    switch(i){

      case 0:
      tourner(carte, r2d2, gauche_rel(r2d2));
      if ((mur(carte, r2d2)==0)) {
        deplacement_initial(carte, r2d2, ligs, cols, pcompt, infoGraph);

      }else {
        tourner(carte, r2d2, oppose(r2d2));
        deplacement_initial(carte, r2d2, ligs, cols, pcompt, infoGraph);

      }
      i++;
      break;
      case 1:
      while((r2d2->ext==0)){
        mouvement_mur(carte, r2d2);
        usleep(10000);
        system("clear");
        afficher(carte, ligs, cols, infoGraph);
        printf("\n");
        pcompt++;
      }
      break;

    }
  }
}

void fct_ilo_map(char** carte, sRobot* r2d2, int ligs,int cols, int* pcompt,  sGraph infoGraph){

    while(r2d2->ext==0){
      switch (r2d2->orientation) {
        case NORD:
        tourner(carte, r2d2, gauche_rel(r2d2));
        r2d2->spx=r2d2->posx;
        r2d2->spy=r2d2->posy;
        while ((mur(carte, r2d2)!=1)&&(sortie(carte, r2d2)==0)){
          deplacement_robot(carte, r2d2);
          usleep(10000);
          system("clear");
          afficher(carte, ligs, cols, infoGraph);
        }
        r2d2->orientation=oppose(r2d2);
        while ((r2d2->spx!=r2d2->posx)&&(sortie(carte, r2d2)==0)){
          deplacement_robot(carte, r2d2);
          usleep(10000);
          system("clear");
          afficher(carte, ligs, cols, infoGraph);
        }
        r2d2->ext=sortie(carte, r2d2);
        tourner(carte, r2d2, gauche_rel(r2d2));
        mouvement_mur(carte, r2d2);
        afficher(carte, ligs, cols, infoGraph);
        break;
        case OUEST:
        tourner(carte, r2d2, gauche_rel(r2d2));
        r2d2->spx=r2d2->posx;
        r2d2->spy=r2d2->posy;

        while ((mur(carte, r2d2)!=1)&&(sortie(carte, r2d2)==0)){
          deplacement_robot(carte, r2d2);
          usleep(10000);
          system("clear");
          afficher(carte, ligs, cols, infoGraph);

        }
        r2d2->orientation=oppose(r2d2);
        while ((r2d2->spy!=r2d2->posy)&&(sortie(carte, r2d2)==0)){
          deplacement_robot(carte, r2d2);
          usleep(10000);
          system("clear");
          afficher(carte, ligs, cols, infoGraph);
        }
        r2d2->ext=sortie(carte, r2d2);
        tourner(carte, r2d2, gauche_rel(r2d2));
        mouvement_mur(carte, r2d2);
        afficher(carte, ligs, cols, infoGraph);
        break;
        case EST:
        tourner(carte, r2d2, gauche_rel(r2d2));
        r2d2->spx=r2d2->posx;
        r2d2->spy=r2d2->posy;
        while ((mur(carte, r2d2)!=1)&&(sortie(carte, r2d2)==0)){
          deplacement_robot(carte, r2d2);
          usleep(10000);
          system("clear");
          afficher(carte, ligs, cols, infoGraph);
        }
        r2d2->orientation=oppose(r2d2);
        while ((r2d2->spy!=r2d2->posy)&&(sortie(carte, r2d2)==0)){
          deplacement_robot(carte, r2d2);
          usleep(10000);
          system("clear");
          afficher(carte, ligs, cols, infoGraph);
        }
        r2d2->ext=sortie(carte, r2d2);
        tourner(carte, r2d2, gauche_rel(r2d2));
        mouvement_mur(carte, r2d2);
        afficher(carte, ligs, cols, infoGraph);
        break;
        case SUD:
        tourner(carte, r2d2, gauche_rel(r2d2));
        r2d2->spx=r2d2->posx;
        r2d2->spy=r2d2->posy;
        while ((mur(carte, r2d2)!=1)&&(sortie(carte, r2d2)==0)){
          deplacement_robot(carte, r2d2);
          usleep(10000);
          system("clear");
          afficher(carte, ligs, cols, infoGraph);
        }
        r2d2->orientation=oppose(r2d2);
        while ((r2d2->spx!=r2d2->posx)&&(sortie(carte, r2d2)==0)){
          deplacement_robot(carte, r2d2);
          usleep(10000);
          system("clear");
          afficher(carte, ligs, cols, infoGraph);
        }
        r2d2->ext=sortie(carte, r2d2);
        tourner(carte, r2d2, gauche_rel(r2d2));
        mouvement_mur(carte, r2d2);
        afficher(carte, ligs, cols, infoGraph);
        break;


      }
    }
  }


int sortie(char** carte,sRobot* r2d2){
  if ((carte[r2d2->posy-1][r2d2->posx]=='S')||(carte[r2d2->posy+1][r2d2->posx]=='S')||(carte[r2d2->posy][r2d2->posx-1]=='S')||(carte[r2d2->posy][r2d2->posx+1]=='S')) {
    //exit(0);
    return 1;
  }
  else return 0;
}
