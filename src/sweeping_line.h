#ifndef SWEEPING_LINE_H
#define SWEEPING_LINE_H

#include <SDL.h>

typedef struct {
    int x, y;
    int dx, dy;
    int length;
    int width;
    int speed; // Velocidad individual de la línea
    SDL_Color color;
    int collision_cooldown; // Tiempo de espera para evitar colisiones múltiples

} SweepingLine;

void init_sweeping_line(SweepingLine *line, int x, int y, int dx, int dy, int length, int width, int speed, SDL_Color color);
void update_sweeping_line(SweepingLine *line, SweepingLine lines[], int num_lines);
void render_sweeping_line(SweepingLine *line, SDL_Renderer *renderer);

#endif // SWEEPING_LINE_H
