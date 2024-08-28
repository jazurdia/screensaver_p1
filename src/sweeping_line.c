// sweeping_line.c
#include "sweeping_line.h"
#include "config.h"
#include <stdlib.h>

void init_sweeping_line(SweepingLine *line, int x, int y, int dx, int dy, int length, int width, int speed, SDL_Color color) {
    line->x = x;
    line->y = y;
    line->dx = dx;
    line->dy = dy;
    line->length = length;
    line->width = width;
    line->speed = speed;
    line->color = color;
    line->collision_cooldown = 0;
}

bool update_sweeping_line(SweepingLine *line, SweepingLine **lines, int *num_lines) {
    line->x += line->dx * line->speed;
    line->y += line->dy * line->speed;

    if (line->collision_cooldown > 0) {
        line->collision_cooldown -= 16;
    }

    if (line->x <= 0 || line->x + line->length >= SCREEN_WIDTH) line->dx = -line->dx;
    if (line->y <= 0 || line->y + line->width >= SCREEN_HEIGHT) line->dy = -line->dy;

    if (line->collision_cooldown <= 0) {
        for (int i = 0; i < *num_lines; i++) {
            if (&(*lines)[i] != line) {
                int distance_x = abs((*lines)[i].x - line->x);
                int distance_y = abs((*lines)[i].y - line->y);

                if (distance_x < line->length && distance_y < line->width) {
                    int overlap_x = line->length - distance_x;
                    int overlap_y = line->width - distance_y;
                    line->x -= overlap_x * (line->x - (*lines)[i].x) / line->length;
                    line->y -= overlap_y * (line->y - (*lines)[i].y) / line->width;
                    line->dx = -line->dx;
                    line->dy = -line->dy;
                    line->collision_cooldown = 1000;

                    // Crear nueva línea si no se ha alcanzado el límite
                    if (*num_lines < MAX_LINES) {
                        SweepingLine new_line;
                        init_sweeping_line(&new_line, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, (rand() % 2 == 0) ? 1 : -1, (rand() % 2 == 0) ? 1 : -1, 20 + rand() % 100, 20 + rand() % 100, 1 + rand() % 5, (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255});
                        *lines = realloc(*lines, (*num_lines + 1) * sizeof(SweepingLine));
                        (*lines)[*num_lines] = new_line;
                        (*num_lines)++;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void render_sweeping_line(SweepingLine *line, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, line->color.r, line->color.g, line->color.b, line->color.a);
    SDL_Rect rect = {line->x, line->y, line->length, line->width};
    SDL_RenderFillRect(renderer, &rect);
}