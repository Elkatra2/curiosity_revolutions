#include "robot.h"

void init_robot(Robot *r, int x, int y, Orientation o) {
    r->x = x;
    r->y = y;
    r->o = o;
}

/*  

            NORD
              |
    Ouest ----X---- Est
              |
             Sud

 */

void avancer(Robot *r) {
    switch(r->o) {
        case Nord:  
            r->x--; 
            return;

        case Est:   
            r->y++; 
            return;

        case Sud:   
            r->x++; 
            return;

        case Ouest: 
            r->y--; 
            return;
    }
}

void tourner_a_gauche(Robot *r) {
    switch(r->o) {
        case Nord:  r->o = Ouest;   return;
        case Ouest: r->o = Sud;     return;
        case Sud:   r->o = Est;     return;
        case Est:   r->o = Nord;    return;
    }
}

void tourner_a_droite(Robot *r) {
    switch(r->o) {
        case Nord:  r->o = Est;     return;
        case Est:   r->o = Sud;     return;
        case Sud:   r->o = Ouest;   return;
        case Ouest: r->o = Nord;    return;
    }
}

void position(Robot *r, int *x, int *y) {
    *x = r->x;
    *y = r->y;
}

int abscisse(Robot *r) { return r->y; }
int ordonnee(Robot *r) { return r->x; }
Orientation orient(Robot *r) { return r->o; }

void position_devant(Robot *r, int *x, int *y) {
    switch(r->o) {
        case Nord:  
            *x = r->x; 
            *y = r->y + 1; 
            return;

        case Est:   
            *x = r->x + 1; 
            *y = r->y;
            return;

        case Sud:   
            *x = r->x;
            *y = r->y - 1; 
            return;

        case Ouest: 
            *x = r->x - 1; 
            *y = r->y;
            return;
    }
}