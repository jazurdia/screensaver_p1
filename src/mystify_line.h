#ifndef MYSTIFY_LINE_H
#define MYSTIFY_LINE_H

#include <SDL.h>

#define MAX_POINTS 4 // Número máximo de puntos de inflexión

typedef struct {
    int points[MAX_POINTS][2]; // Coordenadas de los puntos de inflexión
    int dx[MAX_POINTS];        // Direcciones en X para cada segmento
    int dy[MAX_POINTS];        // Direcciones en Y para cada segmento
    SDL_Color color;           // Color de la línea
    int speed;                 // Velocidad de la línea
} MystifyLine;

void init_mystify_line(MystifyLine *line, int speed, SDL_Color color);
void update_mystify_line(MystifyLine *line);
void render_mystify_line(MystifyLine *line, SDL_Renderer *renderer);

#endif // MYSTIFY_LINE_H
