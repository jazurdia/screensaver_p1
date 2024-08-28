#include <SDL.h>
#include <stdbool.h>
#include "config.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "circle.h"
#include "mystify_line.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    clock_t start_time = clock();

    SDL_Window *window = SDL_CreateWindow("Sweeping Lines and Circles",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SweepingLine lines[NUM_LINES];
    Circle circles[NUM_CIRCLES];

    // Inicializar líneas con posiciones, direcciones, y velocidades aleatorias
    for (int i = 0; i < NUM_LINES; ++i) {
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        int dx = (rand() % 2 == 0) ? 1 : -1;
        int dy = (rand() % 2 == 0) ? 1 : -1;

        int length = 20 + rand() % 100; // Longitud aleatoria entre 10 y 110
        int width = 5 + rand() % 5; // Ancho aleatorio entre 1 y 5

        int speed = 1 + rand() % 5; // Velocidad aleatoria entre 1 y 5
        SDL_Color color = {rand() % 256, rand() % 256, rand() % 256, 255};
        init_sweeping_line(&lines[i], x, y, dx, dy, length, width, speed, color);
    }

    // Inicializar círculos con posiciones, direcciones, y velocidades aleatorias
    for (int i = 0; i < NUM_CIRCLES; ++i) {
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        int dx = (rand() % 2 == 0) ? 1 : -1;
        int dy = (rand() % 2 == 0) ? 1 : -1;

        int radius = 20 + rand() % 30; // Radio aleatorio entre 10 y 40
        int speed = 5 + rand() % 5; // Velocidad aleatoria entre 1 y 5

        SDL_Color color = {rand() % 256, rand() % 256, rand() % 256, 255};
        init_circle(&circles[i], x, y, dx, dy, radius, speed, color);
    }

    MystifyLine mystify_lines[NUM_MYSTIFY_LINES];

    // Iniciar lineas mystify_line
    for (int i = 0; i < NUM_MYSTIFY_LINES; i++) {
        int speed = 1 + rand() % 5; // Velocidad aleatoria entre 1 y 5
        SDL_Color color = {rand() % 256, rand() % 256, rand() % 256, 255};
        init_mystify_line(&mystify_lines[i], speed, color);
    }


    uint32_t frameStart, frameTime;
    char title[] = "FPS: ";

    bool running = true;
    while (running) {
        frameStart = SDL_GetTicks();
        clock_t current_time = clock();
        double elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;
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

        for (int i = 0; i < NUM_CIRCLES; ++i) {
            update_circle(&circles[i], lines, NUM_LINES, circles, NUM_CIRCLES);
            render_circle(&circles[i], renderer);
        }

        for (int i = 0; i < NUM_MYSTIFY_LINES; i++) {
            update_mystify_line(&mystify_lines[i]);
            render_mystify_line(&mystify_lines[i], renderer);
        }

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime > 0) {
            char title[50];
            sprintf(title, "FPS: %.2f", 1000.0 / frameTime);
            SDL_SetWindowTitle(window, title);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
