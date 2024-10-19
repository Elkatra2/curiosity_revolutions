#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <stdio.h>

typedef enum { LIBRE, EAU, ROCHER } Case;

#define DIM_MAX 256

// indexation utilisée :
//  1er  indice : abscisse = colonne (colonne de gauche : abscisse = 0)
//  2ème indice : ordonnée = ligne   (ligne du haut     : ordonnée = 0)

typedef struct {
  int largeur, hauteur;
  Case tab[DIM_MAX][DIM_MAX];
} Terrain;

typedef enum { 
   TERRAIN_OK, ERREUR_FICHIER, ERREUR_LARGEUR_EOF, ERREUR_LARGEUR_NEGATIF, 
   ERREUR_LARGEUR_TROP_GRAND, ERREUR_HAUTEUR_EOF, ERREUR_HAUTEUR_NEGATIF, 
   ERREUR_HAUTEUR_TROP_GRAND, ERREUR_TERRAIN_EOF, ERREUR_TERRAIN_LARGEUR, 
   ERREUR_TERRAIN_HAUTEUR, ERREUR_TERRAIN_CURIOSITY_DEUX, ERREUR_CURIOSITY_DISPARAIT,
   ERREUR_FICHIER_GRAND
} erreur_terrain;

/* Lecture d'un terrain dans un fichier f, ouvert en lecture
   Résultats :
   t le terrain lu
   x, y position initiale du robot lue dans le fichier terrain
   Renvoie :
      TERRAIN_OK:
         - si la lecture s'est déroulée correctement,
      ERREUR_FICHIER:
         - si le fichier n'a pas pu être ouvert,
      ERREUR_LARGEUR_EOF:
         - si au lieu de largeur on a le fin de fichier
      ERREUR_LARGEUR_NEGATIF:
         - si la largeur est plus petit que 0
      ERREUR_LARGEUR_TROP_GRAND:
         - si la largeur est plus grand que DIM_MAX
      ERREUR_HAUTEUR_EOF:
         - si au lieu de l'hauteur on a le fin de fichier
      ERREUR_HAUTEUR_NEGATIF:
         - si l'hauteur est plus petit que 0
      ERREUR_HAUTEUR_TROP_GRAND:
         - si l'hauteur est plus grand que DIM_MAX
      ERREUR_TERRAIN:
         - si le terrain n'est pas bon.
      ..... : // TODO autres erreurs
         - si ....
 */
erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y);

/* Largeur d'un terrain */
int largeur(Terrain *t);

/* Hauteur d'un terrain */
int hauteur(Terrain *t);

/* Indique si la case de coordonnées (x,y) est libre
   Renvoie vrai ssi les 3 conditions suivantes sont vraies :
    - 0 <= x < largeur
    - 0 <= y < hauteur
    - t.tab[x][y] = LIBRE
 */
int est_case_libre(Terrain *t, int x, int y);

/* Affichage d'un terrain t sur la sortie standard */
void afficher_terrain(Terrain *t);

/* Affichage d'un terrain t sur la fenetre graphique */
void afficher_terrain_graphique(Terrain *t);

/* Écriture d'un terrain t dans un fichier f ouvert en écriture.
   x et y contiennent les coordonnées du robot
   Le terrain est écrit au format lisible par lire_terrain */
void ecrire_terrain(FILE *f, Terrain *t, int x, int y);

#endif
