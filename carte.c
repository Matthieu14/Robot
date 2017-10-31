#include "pages.h"

char** recuperationcarte(int* pcols, int*pligs, char* nfichier){
  int x, y, i;
  char **carte;
  FILE *fichier = fopen(nfichier, "r+"); //On ouvre le fichier, puis on vérifie qu'il est existant
  if (fichier == NULL) {
    printf("Problème de chargement du fichier \n");
    return 0;
  }
  fscanf(fichier, "%d:%d", &x, &y); //on récupère les dimensions de la carte
//  printf("nombre de colone(s) : %d\n", x);//on vérifie que ce sont les bonnes dimensions en les affichants
// printf("nombre de ligne(s) : %d\n", y);
  getc(fichier);
  /*--- On renvoie nos variable aux main pour la suite ---*/
  *pcols=x;
  *pligs=y;
  /* on creer un tableau a deux dimensions pour la carte */

  carte = (char**)malloc(sizeof(char*)*y);
  for ( i = 0; i < y; i++) {
    carte[i]= (char*)malloc(sizeof(char)*x);
  }

  for ( i = 0; i < y; i++) {
    fgets(carte[i], x+1, fichier); //on remplis les caractères de la carte
    getc(fichier);
  }


  fclose(fichier); //Fermeture du fichier

  return carte;
}

void afficher(char** carte, int ligs, int cols, sGraph infoGraph){
  int i,j;

  for ( i = 0; i < ligs; i++) {
    for ( j = 0; j < cols; j++) {
      printf("%c", carte[i][j]);
      afficher_bloc( i, j, carte[i][j], infoGraph);
    }
    printf("\n");
  }
  SDL_Flip(infoGraph.ecran);

}
