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
    public:
    Screen()
    {
        SDL_Init(SDL_INIT_VIDEO);
        
        SDL_CreateWindowAndRenderer(
            400*2, 
            300*2,
            0,
            &window,
            &renderer
        );
        /* 
        window = SDL_CreateWindow(
            "Pixel",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640*2, 480*2,
            SDL_WINDOW_SHOWN
        );
        */        

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
