#include "pages.h"

int main(int argc, char ** argv) {
  char ** carte;


  if (argc != 2) {
    printf("Vous n'avez pas rentrer le nom de la carte");
    return 0;
  }


    /*------ On définit des pointeurs pour les nombre de colones et lignes de la carte ainsi que le compteur------*/

    int cols=0;
    int ligs=0;
    int compt=0;
    int ct=0;
    int * pcols=&cols;
    int * pligs=&ligs;
    int* pcompt=&compt;
    //int* pcols=&cols;
    //int* pligs=&ligs;
    sRobot* r2d2;
    sGraph infoGraph;
    srand(time(NULL));


    /*--- Initialisation du robot ---*/

    carte = recuperationcarte(pcols, pligs, argv[1]);
    r2d2=initialiser_sRobot(carte, cols, ligs);


    infoGraph = initialiserGraph(ligs, cols);
    /*--- On commence a le faire déplacer afin de le boquer dans un mur en haut a droite ---*/
    afficher(carte, ligs, cols, infoGraph);
    deplacement_initial(carte, r2d2, ligs, cols, pcompt, infoGraph);
    tourner(carte, r2d2, gauche_rel(r2d2));
    deplacement_initial(carte, r2d2, ligs, cols, pcompt, infoGraph);
    afficher(carte, ligs, cols, infoGraph);

    /*--- On fait tourner le robot près des murs, s'il reviens a sa position initiale on change de méthode d'exploration ---*/
  //  printf("fin");
    //exit(0);
    while(r2d2->ext==0){

      mouvement_mur(carte, r2d2);
      usleep(10000);
      system("clear");
      afficher(carte, ligs, cols, infoGraph);
      printf("\n");
      compt++;
      ct++;
      if (ct>1) {
        if ((r2d2->posx==r2d2->pmx)&&(r2d2->posy==r2d2->pmy)) {
          fct_ilo_map(carte, r2d2, ligs,cols, pcompt, infoGraph);
        }
      }
      if ( !rafraichit(infoGraph)){
        return 0;
      }
    }
    if (compt==1) {
      printf("Le robot a trouver la sortie en une seule étape !\n");
    }
    else printf("le robot a trouvé la sortie en %d étapes !\n", compt);


    return 0;
  //}
}
