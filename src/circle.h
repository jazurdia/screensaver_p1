#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL.h>

#include "sweeping_line.h"

typedef struct {
    int x, y;
    int dx, dy;
    int radius;  // Radio del círculo
    int speed;   // Velocidad del círculo
    SDL_Color color;
    int collision_cooldown; // Tiempo de espera para evitar colisiones múltiples
} Circle;

void init_circle(Circle *circle, int x, int y, int dx, int dy, int radius, int speed, SDL_Color color);
void update_circle(Circle *circle, SweepingLine lines[], int num_lines, Circle circles[], int num_circles);
void render_circle(Circle *circle, SDL_Renderer *renderer);

#endif // CIRCLE_H
