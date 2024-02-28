#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <numeric>
#include <iostream>

class Screen
{
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;
    bool isFullscreen;
    public:
    Screen(bool isScreenSaver)
    {
        isFullscreen = false;

        SDL_Init(SDL_INIT_VIDEO);
        if(isScreenSaver)
        {
            window = SDL_CreateWindow(
                "ScreenSaver",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                400*2, 300*2,
                SDL_WINDOW_FULLSCREEN_DESKTOP
            );
            renderer = SDL_CreateRenderer(window, -1, 0);
        } 
        else 
        {
        SDL_CreateWindowAndRenderer(
            400*2, 
            300*2,
            0,
            &window,
            &renderer
        );
        }
        

        SDL_RenderSetScale(renderer, 2, 2);
    }

    void pixel(float x, float y) 
    {
        points.emplace_back(x,y);
    }

    void show()
    {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
    
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(auto& point: points)
        {
            SDL_RenderDrawPointF(renderer, point.x, point.y);

        }

        SDL_RenderPresent(renderer);
    }

    void clear()
    {
        points.clear();
    }

    void input() 
    {
        while(SDL_PollEvent(&e) != 0) 
        {
            switch(e.type) 
            {
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);

                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_f) {
                        isFullscreen = !isFullscreen;
                        SDL_SetWindowFullscreen(window, isFullscreen ? SDL_WINDOW_FULLSCREEN : 0);
                    }
            }
            
            /*
            if(e.type == SDL_QUIT) 
            {
                SDL_Quit();
                exit(0);
            }
            */

        }
    }
};
