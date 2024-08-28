#include "mystify_line.h"
#include "config.h"
#include <stdlib.h>

void init_mystify_line(MystifyLine *line, int speed, SDL_Color color) {
    line->speed = speed;
    line->color = color;

    // Inicializar puntos de inflexión y direcciones
    for (int i = 0; i < MAX_POINTS; i++) {
        line->points[i][0] = rand() % SCREEN_WIDTH;
        line->points[i][1] = rand() % SCREEN_HEIGHT;
        line->dx[i] = (rand() % 2 == 0) ? 1 : -1;
        line->dy[i] = (rand() % 2 == 0) ? 1 : -1;
    }
}

void update_mystify_line(MystifyLine *line) {
    for (int i = 0; i < MAX_POINTS; i++) {
        // Actualizar la posición de cada punto
        line->points[i][0] += line->dx[i] * line->speed;
        line->points[i][1] += line->dy[i] * line->speed;

        // Rebotar en los bordes de la pantalla
        if (line->points[i][0] <= 0 || line->points[i][0] >= SCREEN_WIDTH)
            line->dx[i] = -line->dx[i];
        if (line->points[i][1] <= 0 || line->points[i][1] >= SCREEN_HEIGHT)
            line->dy[i] = -line->dy[i];
    }

    // Cambiar el color gradualmente
    line->color.r = (line->color.r + 1) % 256;
    line->color.g = (line->color.g + 2) % 256;
    line->color.b = (line->color.b + 3) % 256;
}

void render_mystify_line(MystifyLine *line, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, line->color.r, line->color.g, line->color.b, line->color.a);

    // Dibujar la línea conectando los puntos de inflexión
    for (int i = 0; i < MAX_POINTS - 1; i++) {
        SDL_RenderDrawLine(renderer, line->points[i][0], line->points[i][1],
                           line->points[i + 1][0], line->points[i + 1][1]);
    }
}
