#ifndef APP_HPP
#define APP_HPP

#include <vector>
#include <SDL3/SDL.h>
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

        // Frees Media and shutdowns SDL
        void close();

        // Render functions.
        void beginFrame();
        void beginFrame(Color& c);
        void endFrame();

        int getScreenWidth() const;
        int getScreenHeight() const;
        
        SDL_Renderer* getRenderer() const;
        SDL_Window* getWindow() const;
    
    private:
        // The window and renderer
        WindowAndRenderer windowAndRenderer;
        ScreenCfg screenCfg;

        void setDrawColor(Color& color);
    };
}

#endif // !APP_HPP