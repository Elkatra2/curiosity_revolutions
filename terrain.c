#include "graphique.h"
#include "terrain.h"
#include "robot.h"

#include <stdio.h>
#include <string.h>

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y) {
  int l, h = 0;   // Dimensions du terrain
  int rx, ry = 0; // Coordonnées initiales du robot

  if (f == NULL) {
    return ERREUR_FICHIER;
  }

  // Lecture de la largeur
  fscanf(f, "%d", &l);
  t->largeur = l;

  // Lecture de la hauteur
  fscanf(f, "%d", &h);
  t->hauteur = h;

  // Lecture du terrain
  fgetc(f); // mange '\n'
  char ligne[DIM_MAX];
  for (int i = 0; i < h; i++) {
    fgets(ligne, DIM_MAX, f);
    for (int j = 0; j < l; j++) {
      switch(ligne[j]) {
        case '.':
          t->tab[i][j] = LIBRE;
          break;
        case '#':
          t->tab[i][j] = ROCHER;
          break;
        case '~':
          t->tab[i][j] = EAU;
          break;
        case 'C':
          t->tab[i][j] = LIBRE;
          ry = i;
          rx = j;
          break;
      }
    }
  }

  // Initialisation de la position du robot
  *x = rx;
  *y = ry;

  return OK;
}

int largeur(Terrain *t) {
  return t->largeur;
}

int hauteur(Terrain *t) {
  return t->hauteur;
}

int est_case_libre(Terrain *t, int x, int y) {
  if ((0 <= x && x < largeur(t)) && (0 <= y && y <= hauteur(t)) && t->tab[x][y] == LIBRE) {
    return 1;
  } else {
    return 0;
  }
}

void afficher_terrain(Terrain *t) {
  for (int i = 0; i < hauteur(t); i++) {
    for (int j = 0; j < largeur(t); j++) {
      switch(t->tab[i][j]) {
        case LIBRE:
          putchar('.');
          break;
        case ROCHER:
          putchar('#');
          break;
        case EAU:
          putchar('~');
          break;
      }
    }
    putchar('\n');
  }
}

#ifdef AFFICHE_GRAPH

#define POS_X 310
#define POS_Y 110

void afficher_terrain_graphique(Terrain *t) {
  for (int i = 0; i < hauteur(t); i++) {
    for (int j = 0; j < largeur(t); j++) {
      switch(t->tab[i][j]) {
        case LIBRE:
          DrawText(".", POS_X + j * 20 + 5, POS_Y + i * 20 - 6, 20, WHITE);
          break;
        case ROCHER:
          DrawText("#", POS_X + j * 20, POS_Y + i * 20, 20, WHITE);
          break;
        case EAU:
          DrawText("~", POS_X + j * 20, POS_Y + i * 20, 20, WHITE);
          break;
      }
    }
  }
}

#else 

void afficher_terrain_graphique(Terrain *t) {  }

#endif

/* Écriture d'un terrain t dans un fichier f ouvert en écriture.
   x et y contiennent les coordonnées du robot
   Le terrain est écrit au format lisible par lire_terrain */
void ecrire_terrain(FILE *f, Terrain *t, int x, int y);