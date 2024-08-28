// circle.c
#include "circle.h"
#include "config.h"
#include <math.h>
#include <stdlib.h>

void init_circle(Circle *circle, int x, int y, int dx, int dy, int radius, int speed, SDL_Color color) {
    circle->x = x;
    circle->y = y;
    circle->dx = dx;
    circle->dy = dy;
    circle->radius = radius;
    circle->speed = speed;
    circle->color = color;
    circle->collision_cooldown = 0;
}

bool update_circle(Circle *circle, SweepingLine *lines, int num_lines, Circle **circles, int *num_circles) {
    circle->x += circle->dx * circle->speed;
    circle->y += circle->dy * circle->speed;

    if (circle->collision_cooldown > 0) {
        circle->collision_cooldown -= 16;
    }

    if (circle->x - circle->radius <= 0 || circle->x + circle->radius >= SCREEN_WIDTH) circle->dx = -circle->dx;
    if (circle->y - circle->radius <= 0 || circle->y + circle->radius >= SCREEN_HEIGHT) circle->dy = -circle->dy;

    if (circle->collision_cooldown <= 0) {
        for (int i = 0; i < num_lines; i++) {
            int distance_x = abs(lines[i].x - circle->x);
            int distance_y = abs(lines[i].y - circle->y);

            if (distance_x < lines[i].length && distance_y < circle->radius) {
                circle->dx = -circle->dx;
                circle->dy = -circle->dy;
                circle->collision_cooldown = 1000;

                // Crear nuevo círculo
                Circle new_circle;
                init_circle(&new_circle, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, (rand() % 2 == 0) ? 1 : -1, (rand() % 2 == 0) ? 1 : -1, 20 + rand() % 30, 5 + rand() % 5, (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255});
                *circles = realloc(*circles, (*num_circles + 1) * sizeof(Circle));
                (*circles)[*num_circles] = new_circle;
                (*num_circles)++;
                return true;
            }
        }
    }

    if (circle->collision_cooldown <= 0) {
        for (int i = 0; i < *num_circles; i++) {
            if (&(*circles)[i] != circle) {
                int distance = sqrt(pow((*circles)[i].x - circle->x, 2) + pow((*circles)[i].y - circle->y, 2));
                if (distance < circle->radius + (*circles)[i].radius) {
                    int overlap = circle->radius + (*circles)[i].radius - distance;
                    int total_radius = circle->radius + (*circles)[i].radius;
                    circle->x -= overlap * (circle->x - (*circles)[i].x) / total_radius;
                    circle->y -= overlap * (circle->y - (*circles)[i].y) / total_radius;
                    circle->dx = -circle->dx;
                    circle->dy = -circle->dy;
                    circle->collision_cooldown = 1000;

                    // Crear nuevo círculo
                    Circle new_circle;
                    init_circle(&new_circle, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, (rand() % 2 == 0) ? 1 : -1, (rand() % 2 == 0) ? 1 : -1, 20 + rand() % 30, 5 + rand() % 5, (SDL_Color){rand() % 256, rand() % 256, rand() % 256, 255});
                    *circles = realloc(*circles, (*num_circles + 1) * sizeof(Circle));
                    (*circles)[*num_circles] = new_circle;
                    (*num_circles)++;
                    return true;
                }
            }
        }
    }
    return false;
}

void render_circle(Circle *circle, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, circle->color.a);
    for (int w = 0; w < circle->radius * 2; w++) {
        for (int h = 0; h < circle->radius * 2; h++) {
            int dx = circle->radius - w;
            int dy = circle->radius - h;
            if ((dx * dx + dy * dy) <= (circle->radius * circle->radius)) {
                SDL_RenderDrawPoint(renderer, circle->x + dx, circle->y + dy);
            }
        }
    }
}