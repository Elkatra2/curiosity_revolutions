#include "graphique.h"
#include "terrain.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *f;
  Terrain t;
  int x, y;

  erreur_terrain err;
  char buf[BUFSIZ];

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");
  err = lire_terrain(f, &t, &x, &y);  
  while (err == ERREUR_FICHIER) {
    printf("Nouveau fichier: ");
    fscanf(stdin, "%s", buf);

    f = fopen(buf, "r");
    err = lire_terrain(f, &t, &x, &y);
  }
  
  fclose(f);
  if (err == TERRAIN_OK) {
    afficher_terrain(&t);
    printf("Position initiale du robot : (%d, %d)\n", x, y);
  }
  
  return err;
}