#include "graphique.h"
#include "terrain.h"

#include "erreur.h"

#include <stdio.h>
#include <string.h>

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y) {
  int l, h = 0; // Dimensions du terrain
  int rx, ry = 0; // Coordonnées initiales du robot
  bool deja_vu_curiosity = false; // Si on avait deja lu le Curiosity ou pas

  if (f == NULL) {
    ERREUR("Erreur de lecture !\n")
    return ERREUR_FICHIER;
  }

  // Lecture de la largeur
  if (fscanf(f, "%d", &l) != EOF) {
    if (0 <= l) {
      if (l <= DIM_MAX) {
        t->largeur = l;
      } else {
        ERREUR("La largeur est plus grand que DIM_MAX!\n")
        return ERREUR_LARGEUR_TROP_GRAND;
      }
    } else {
      ERREUR("La largeur est plus petit que 0!\n")
      return ERREUR_LARGEUR_NEGATIF;
    }
  } else {
    ERREUR("Fin du fichier au lieu de largeur!\n")
    return ERREUR_LARGEUR_EOF;
  }

  // Lecture de la hauteur
  if (fscanf(f, "%d", &h) != EOF) {
    if (0 <= h) {
      if (h <= DIM_MAX) {
        t->hauteur = h;
      } else {
        ERREUR("L'hauteur est plus grand que DIM_MAX!\n")
        return ERREUR_HAUTEUR_TROP_GRAND;
      }
    } else {
      ERREUR("L'hauteur est plus petit que 0!\n")
      return ERREUR_HAUTEUR_NEGATIF;
    }
  } else {
    ERREUR("Fin du fichier au lieu de l'hauteur!\n")
    return ERREUR_HAUTEUR_EOF;
  }

  if (fgetc(f) == EOF) { // mange '\n'
    ERREUR("Fin du fichier uu lieu du terrain !\n")
    return ERREUR_TERRAIN_EOF;
  }

  char ligne[DIM_MAX + 1];      // la ligne, DIM_MAX + 1 pour manger a la fin '\n' si la largeur est 256
  int i = 0;                    // l'indice de abscisse
  int j = 0;                    // l'indice d'ordonnée
  char c;                       // courseur de la linge
  for (i = 0; i < h; i++) {
    fgets(ligne, DIM_MAX + 1, f);   // initialise la linge + mange '\n'
    for (j = 0; j < l; j++) {
      c = ligne[j];
      switch(c) {
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
          if (!deja_vu_curiosity) {
            t->tab[i][j] = LIBRE;
            ry = j;
            rx = i;
            deja_vu_curiosity = true;
          } else {
            ERREUR("[%d,%d] On avait déjà vu Curiosity dans (%d,%d)!\n", j, i, rx, ry)
            return ERREUR_TERRAIN_CURIOSITY_DEUX;
          }
          break;
        case '\n':
          if (j != 0) {
            ERREUR("[%d,%d] La largeur du terrain ne satisfait pas la dimension!\n", j, i)
            return ERREUR_TERRAIN_LARGEUR;
          } else {
            ERREUR("[%d,%d] L'hauteur du terrain ne satisfait pas la dimension!\n", j, i)
            return ERREUR_TERRAIN_HAUTEUR;
          }
        case EOF: 
          ERREUR("[%d,%d] Fin du fichier dans la largeur du terrain!\n", j, i)
          return ERREUR_TERRAIN_EOF;
      }
    }
  }
  
  // Initialisation de la position du robot
  if (fgets(ligne, DIM_MAX, f) == NULL) {
    if (deja_vu_curiosity) {
      *x = rx;
      *y = ry;
      return TERRAIN_OK;
    } else {
      ERREUR("On avait jamais vu Curiosity dans le terrain!\n")
      return ERREUR_CURIOSITY_DISPARAIT;
    }
  } else {
    ERREUR("Le fichier est trop grand!\n")
    return ERREUR_FICHIER_GRAND;;
  }
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

#ifdef OFF

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

#endif

/* Écriture d'un terrain t dans un fichier f ouvert en écriture.
   x et y contiennent les coordonnées du robot
   Le terrain est écrit au format lisible par lire_terrain */
void ecrire_terrain(FILE *f, Terrain *t, int x, int y) {
  /* largeur et hauteur du terrain */
  int l = t->largeur;
  int h = t->hauteur;

  /* écrit la largeur dans le fichier. */
  fprintf(f, "%d\n", l);
  
  /* écrit l'hauteur dans le fichier. */
  fprintf(f, "%d\n", h);

  /* écrit le terrain dans le fichier. */
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < l; j++) {
      switch (t->tab[i][j]) {
        case LIBRE:
          // si dans la case il y a Curiosity
          if (j == x && i == y) { 
            putc('C', f); 
          } else { // sinon
            putc('.', f); 
          }
          break;
        case EAU:
          putc('~', f);
          break;
        case ROCHER:
          putc('#', f);
      }
    }
    putc('\n', f);
  }

  fclose(f); // écrit et ferme le fichier.
}