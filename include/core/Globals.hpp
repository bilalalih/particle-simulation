#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <SDL3/SDL.h>
#include "rendering/Texture.hpp"
#include "Config.hpp"

namespace global
{
    // The window we'll be rendering to
    extern core::WindowAndRenderer gWindowAndRenderer;

    // Scene textures
    extern rendering::Texture gPngTexture;

    extern core::ScreenCfg gScreenCfg;
}

#endif // !GLOBALS_HPP