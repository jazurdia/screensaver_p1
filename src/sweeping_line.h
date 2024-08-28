// sweeping_line.h
#ifndef SWEEPING_LINE_H
#define SWEEPING_LINE_H

#include <SDL.h>
#include <stdbool.h>

typedef struct {
    int x, y;
    int dx, dy;
    int length;
    int width;
    int speed;
    SDL_Color color;
    int collision_cooldown;
} SweepingLine;

void init_sweeping_line(SweepingLine *line, int x, int y, int dx, int dy, int length, int width, int speed, SDL_Color color);
bool update_sweeping_line(SweepingLine *line, SweepingLine **lines, int *num_lines);
void render_sweeping_line(SweepingLine *line, SDL_Renderer *renderer);

#endif // SWEEPING_LINE_H