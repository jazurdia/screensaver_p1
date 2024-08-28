// circle.h
#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL.h>
#include <stdbool.h>
#include "sweeping_line.h"

typedef struct {
    int x, y;
    int dx, dy;
    int radius;
    int speed;
    SDL_Color color;
    int collision_cooldown;
} Circle;

void init_circle(Circle *circle, int x, int y, int dx, int dy, int radius, int speed, SDL_Color color);
bool update_circle(Circle *circle, SweepingLine *lines, int num_lines, Circle **circles, int *num_circles);
void render_circle(Circle *circle, SDL_Renderer *renderer);

#endif // CIRCLE_H