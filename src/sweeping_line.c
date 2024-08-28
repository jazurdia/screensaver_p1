#include "sweeping_line.h"
#include "config.h"
#include <math.h>

void init_sweeping_line(SweepingLine *line, int x, int y, int dx, int dy, int length, int width, int speed, SDL_Color color) {
    line->x = x;
    line->y = y;
    line->dx = dx;
    line->dy = dy;
    line->length = length;
    line->width = width;
    line->speed = speed;
    line->color = color;
}

void update_sweeping_line(SweepingLine *line, SweepingLine lines[], int num_lines) {
    // Actualizar la posición usando la velocidad individual
    line->x += line->dx * line->speed;
    line->y += line->dy * line->speed;

    // Rebotar en los bordes de la pantalla
    if (line->x <= 0 || line->x + line->length >= SCREEN_WIDTH) line->dx = -line->dx;
    if (line->y <= 0 || line->y + line->width >= SCREEN_HEIGHT) line->dy = -line->dy;

    // Rebotar con otras líneas
    for (int i = 0; i < num_lines; i++) {
        if (&lines[i] != line) {
            int distance_x = abs(lines[i].x - line->x);
            int distance_y = abs(lines[i].y - line->y);

            // Colisión simple basada en la cercanía
            if (distance_x < line->length && distance_y < line->width) {
                line->dx = -line->dx;
                line->dy = -line->dy;
            }
        }
    }
}

void render_sweeping_line(SweepingLine *line, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, line->color.r, line->color.g, line->color.b, line->color.a);
    SDL_Rect rect = {line->x, line->y, line->length, line->width};
    SDL_RenderFillRect(renderer, &rect);
}
