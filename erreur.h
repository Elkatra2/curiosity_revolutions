#ifndef ERREUR_H
#define ERREUR_H

#include <stdio.h>

// les couleurs
#define E_RED         "\e[0;31m"
#define E_YEL         "\e[0;33m"
#define E_RESET       "\e[0m"

// affiche dans la sortie d'erreur standart
#define eprintf(__format, ...) fprintf(stderr, __format, ##__VA_ARGS__);

/** 
 * Affiche dans la sortie d'erreur standart en couleur rouge. 
 * - l, le nombre de ligne a decaler,
 * - __format, le format d'affichage comme dans printf,
 * - ..., les parametres a passer comme dans prinft pour le format.
*/
#define ERREUR(__format, ...) eprintf(E_RED "Fichier %s:%d dans %s: " __format E_RESET, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#endif // erreur.h