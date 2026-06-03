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
        int screenWidth{ 1280 };
        int screenHeight{ 720 };
    };

    struct Color
    {
        Uint8 r{ 255 };
        Uint8 g{ 255 };
        Uint8 b{ 255 };
        Uint8 a{ 255 };
    };
}
#endif // !CONFIG_HPP