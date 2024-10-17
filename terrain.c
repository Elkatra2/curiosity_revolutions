
#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <string.h>

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y) {
  int l, h;   // Dimensions du terrain
  int rx, ry; // Coordonnées initiales du robot

  if (f == NULL) {
    return ERREUR_FICHIER;
  }

  // Lecture de la largeur
  

  // Lecture de la hauteur
  

  // Lecture du terrain
  

  // Initialisation de la position du robot
  

  return OK;
}

/* À compléter */
