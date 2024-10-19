#include "graphique.h"
#include "terrain.h"

#ifdef OFF

void affiche_test_terrain(Terrain *t, int x, int y) {
#ifdef AFFICHE_GRAPH

  InitWindow(ECRAN_LARGEUR, ECRAN_HAUTEUR, "Curiosity Revolutions");
  SetTargetFPS(60); // FPS de l'écran
  
  // Main game loop
  while (!WindowShouldClose()) { // Détecte l'écran et sortie si on a ESCAPE
      // Mise à jour de variables
      // TODO ...

      BeginDrawing();
          ClearBackground(BLACK);
          afficher_terrain_graphique(t);
      EndDrawing();
  }

  CloseWindow(); // ferme l'écran

#else

  afficher_terrain(t);
  printf("Position initiale du robot : (%d, %d)\n", x, y);

#endif
}

#endif