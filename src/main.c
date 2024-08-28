// main.c
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "circle.h"
#include "sweeping_line.h"
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

    int num_lines = NUM_LINES;
    SweepingLine *lines = malloc(num_lines * sizeof(SweepingLine));
    for (int i = 0; i < num_lines; ++i) {
        init_sweeping_line(&lines[i], rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, (rand() % 2 == 0) ? 1 : -1, (rand() % 2 == 0) ? 1 : -1, 20 + rand() % 100, 20 + rand() % 100, 1 + rand() % 5, (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255});
    }

    int num_circles = NUM_CIRCLES;
    Circle *circles = malloc(num_circles * sizeof(Circle));
    for (int i = 0; i < num_circles; ++i) {
        init_circle(&circles[i], rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, (rand() % 2 == 0) ? 1 : -1, (rand() % 2 == 0) ? 1 : -1, 20 + rand() % 30, 5 + rand() % 5, (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255});
    }

    int num_mystify_lines = NUM_MYSTIFY_LINES;
    MystifyLine *mystify_lines = malloc(num_mystify_lines * sizeof(MystifyLine));
    for (int i = 0; i < num_mystify_lines; i++) {
        init_mystify_line(&mystify_lines[i], 1 + rand() % 5, (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255});
    }

    uint32_t frameStart, frameTime;
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

        for (int i = 0; i < num_lines; ++i) {
            if (update_sweeping_line(&lines[i], &lines, &num_lines)) {
                i--; // Re-evaluate the current index after adding a new line
            }
            render_sweeping_line(&lines[i], renderer);
        }

        for (int i = 0; i < num_circles; ++i) {
            if (update_circle(&circles[i], lines, num_lines, &circles, &num_circles)) {
                i--; // Re-evaluate the current index after adding a new circle
            }
            render_circle(&circles[i], renderer);
        }

        for (int i = 0; i < num_mystify_lines; i++) {
            update_mystify_line(&mystify_lines[i]);
            render_mystify_line(&mystify_lines[i], renderer);
        }

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime > 0) {
            char title[100];
            sprintf(title, "FPS: %.2f | Lines: %d | Circles: %d", 1000.0 / frameTime, num_lines, num_circles);
            SDL_SetWindowTitle(window, title);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    free(lines);
    free(circles);
    free(mystify_lines);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}