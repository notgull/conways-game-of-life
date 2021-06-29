// MIT License

#include "cell.h"

#include <SDL.h>

#include <cstdint>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

int main(int argc, char **argv) {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr; 
    bool quit = false;
    SDL_Event e;

    // space in between each cell, e.g. how many pixels are in between each line of the grid
    uint32_t scale = 10;

    // current x and y for the viewport, e.g. upper-left is on the cell at (x / scale), (y / scale)
    int64_t x = 0;
    int64_t y = 0;

    // is the left mouse button currently down?
    bool click = false;

    // if the left mouse button is down, this is the location of which it was last down
    int last_down_x, last_down_y;
    int cur_down_x, cur_down_y;
    int xc, yc;

    // initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not be initialized: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // create window
    window = SDL_CreateWindow(
        "Conway's Game of Life",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL window could not be created: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // acquire SDL window renderer
    renderer = SDL_CreateRenderer(window, -1, 0); 

    while (!quit) {
        // fill the window with a bluish color
        SDL_SetRenderDrawColor(renderer, 0x22, 0x22, 0x44, 0xFF); 
        SDL_RenderClear(renderer);
    
        // begin drawing the grid
        uint64_t offset_x = abs(x) % scale;
        uint64_t current_x = offset_x;
        uint64_t offset_y = abs(y) % scale;
        uint64_t current_y = offset_y;

        SDL_SetRenderDrawColor(renderer, 0xEE, 0xCC, 0xCC, 0xFF);

        while (current_y <= SCREEN_HEIGHT) {
            SDL_RenderDrawLine(renderer, 0, current_y, SCREEN_WIDTH, current_y);
            current_y += scale;
        }

        while (current_x <= SCREEN_WIDTH) {
            SDL_RenderDrawLine(renderer, current_x, 0, current_x, SCREEN_HEIGHT);
            current_x += scale;
        }

        // update window to show graphics
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                click = true;
                SDL_GetMouseState(&last_down_x, &last_down_y);
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                click = false;
            } else if (e.type == SDL_MOUSEMOTION) {
                if (click) {
                    SDL_GetMouseState(&cur_down_x, &cur_down_y);
                    
                    // calculate the shift
                    xc = cur_down_x - last_down_x;
                    yc = cur_down_y - last_down_y;

                    x += xc;
                    y += yc;

                    last_down_x = cur_down_x;
                    last_down_y = cur_down_y;
                }
            }
        }
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
