#include <SDL3/SDL.h>
#include "rendering/DrawUtils.hpp"

namespace rendering
{
    void drawCircle(SDL_Renderer* renderer, int center_x, int center_y, int radius)
    {
        for (int y = -radius; y <=radius; y++)
        {
            for (int x = -radius; x <= radius; x++)
            {
                if (x*x + y*y <= radius*radius)
                {
                    SDL_RenderPoint(renderer, center_x + x, center_y + y);
                }
            }
        }
    }
}