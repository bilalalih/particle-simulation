#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SDL3/SDL.h>

namespace core
{
    // Screen dimension constants
    struct WindowAndRenderer
    {
        SDL_Renderer* renderer{ nullptr };
        SDL_Window* window{ nullptr };
    };

    struct ScreenCfg
    {
        int screenWidth{ 640 };
        int screenHeight{ 800 };
    };
}
#endif // !CONFIG_HPP