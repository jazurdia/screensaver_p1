#include <SDL.h>
#include <stdbool.h>
#include "config.h"
#include "sweeping_line.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Sweeping Lines",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SweepingLine lines[NUM_LINES];

    // Inicializar líneas con posiciones, direcciones, y velocidades aleatorias
    for (int i = 0; i < NUM_LINES; ++i) {
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        int dx = (rand() % 2 == 0) ? 1 : -1;
        int dy = (rand() % 2 == 0) ? 1 : -1;
        // int length = 100; // Longitud de la línea
        // int width = 5;    // Ancho de la línea

        int length = 50 + rand() % 100; // Longitud aleatoria entre 50 y 150
        int width = 1 + rand() % 10;     // Ancho aleatorio entre 1 y 10

        int speed = 1 + rand() % 5; // Velocidad aleatoria entre 1 y 5
        SDL_Color color = {rand() % 256, rand() % 256, rand() % 256, 255};
        init_sweeping_line(&lines[i], x, y, dx, dy, length, width, speed, color);
    }

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < NUM_LINES; ++i) {
            update_sweeping_line(&lines[i], lines, NUM_LINES);
            render_sweeping_line(&lines[i], renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
