#include "core/App.hpp"

namespace core
{
    bool App::init()
    {
        // Initialization Flag
        bool success{ true };
        
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create Window with Renderer
            if (!SDL_CreateWindowAndRenderer(
                "Particle Simulator", 
                screenCfg.screenWidth, 
                screenCfg.screenHeight,
                0,
                &windowAndRenderer.window,
                &windowAndRenderer.renderer
                )
            ){
                SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
        }

        if (success)
        {
            SDL_Log("SDL initialized successfully\n");
        }

        return success;
    }
    
    void App::close()
    {
        // Destroy Window
        SDL_DestroyRenderer( windowAndRenderer.renderer );
        windowAndRenderer.renderer = nullptr;
        SDL_DestroyWindow( windowAndRenderer.window ); 
        windowAndRenderer.window = nullptr;

        // Quit SDL subsystems
        SDL_Quit();
    }

    void App::beginFrame()
    {
        Color bg{20,20,30,255};

        setDrawColor(bg);

        SDL_RenderClear(
            windowAndRenderer.renderer
        );
    }

    
    void App::beginFrame(const Color& c)
    {
        setDrawColor(c);

        SDL_RenderClear(
            windowAndRenderer.renderer
        );
    }

    void App::endFrame()
    {
        SDL_RenderPresent(
            windowAndRenderer.renderer
        );
    }

    int App::getScreenWidth() const 
    { 
        return screenCfg.screenWidth;
    }

    int App::getScreenHeight() const 
    { 
        return screenCfg.screenHeight; 
    }

    SDL_Renderer* App::getRenderer() const
    {
        return windowAndRenderer.renderer;
    }

    SDL_Window* App::getWindow() const
    {
        return windowAndRenderer.window;
    }

    void App::setDrawColor(const Color& color)
    {
        SDL_SetRenderDrawColor(windowAndRenderer.renderer, color.r, color.g, color.b, color.a);
    }
}