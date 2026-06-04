#ifndef APP_HPP
#define APP_HPP

#include <vector>
#include <SDL3/SDL.h>
#include "rendering/Texture.hpp"
#include "particles/Particle.hpp"
#include "core/Config.hpp"

namespace core
{
    struct App
    {        
    public:
        App(WindowAndRenderer windowAndRenderer_, ScreenCfg cfg_)
        :
            windowAndRenderer(windowAndRenderer_),
            screenCfg(cfg_)
        {
        }
        
        // Starts up SDL and creates window
        bool init();

        // Loads media
        bool loadMedia(const std::string& path);
        bool loadFourMediaTextures(
        const std::string& path_up = "./assets/up.png",
        const std::string& path_down = "./assets/down.png",
        const std::string& path_left = "./assets/left.png",
        const std::string& path_right = "./assets/right.png"
        );

        // Frees Media and shutdowns SDL
        void close();

        // Render functions.
        void beginFrame();
        void beginFrame(Color& c);
        void drawParticle(
            Color& color,
            Particle& particle
        );
        void endFrame();
        void render_img(Color& color);
        void render_rectangle_with_dark_background(Color& color);

        int getScreenWidth() const;

        int getScreenHeight() const;

        SDL_Renderer* getRenderer() const;
        
        SDL_Window* getWindow() const;

        rendering::Texture& getUpTexture();
        rendering::Texture& getDownTexture();
        rendering::Texture& getLeftTexture();
        rendering::Texture& getRightTexture();

        void setDrawColor(Color& color);
    private:
        // The window and renderer
        WindowAndRenderer windowAndRenderer;
        // The PNG Texture
        rendering::Texture pngTexture;
        // The screen configuration (width and height)
        ScreenCfg screenCfg;
        
        // The directional images
        rendering::Texture upTexture, downTexture, leftTexture, rightTexture;
    };
}

#endif // !UTILS_HPP