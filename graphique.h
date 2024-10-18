#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include "raylib.h"
#include "terrain.h"

/* Affichage graphique avec le flag SHOW_GRAPH */

/* Mode graphique */
#ifdef AFFICHE_GRAPH
    #define ECRAN_LARGEUR 800
    #define ECRAN_HAUTEUR 450
#endif

/** Affiche le test terrain 
 * Paramètres:
 * - t, le terrain
 * - x, y les coordonnée de Curiosity
*/
void affiche_test_terrain(Terrain *t, int x, int y);

#endif // affichage.h