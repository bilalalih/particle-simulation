#include "core/Utils.hpp"

namespace core
{
    bool app::init(const ScreenCfg& screenCfg_)
    {
        // Initialization Flag
        bool success{ true };
        
        if (SDL_Init(SDL_INIT_VIDEO) == false)
        {
            SDL_Log("SDL could not initialize! SDL Error: %s/n", SDL_GetError());
            success = false;
        } else 
        {
            // Create Window with Renderer
            if (SDL_CreateWindowAndRenderer(
                "Particle SImulation: Texture And Extension Libraries", 
                screenCfg_.screenWidth, 
                screenCfg_.screenHeight,
                0,
                &windowAndRenderer.window,
                &windowAndRenderer.renderer
                ) == false
            ){
                SDL_Log("Window Could Not Be Created! SDL Error: %s/n", SDL_GetError());
                success = false;
            }
            // set screen configuration
            screenCfg.screenHeight = screenCfg_.screenHeight;
            screenCfg.screenWidth = screenCfg_.screenWidth;
        }

        SDL_Log("SDL Initialized Succesfully");
        return success;
    }

    bool app::loadMedia(const std::string& path)
    {
        // File loading flag
        bool success{ true };

        // Load splash image
        if (pngTexture.loadFromFile(path, windowAndRenderer.renderer) == false)
        {
            SDL_Log("Unable To Load PNG Image!\n");
            success = false;
        }

        return success;
    }

    void app::close()
    {

        // Clean up Texture
        pngTexture.destroy();

        // Destroy Window
        SDL_DestroyRenderer( windowAndRenderer.renderer );
        windowAndRenderer.renderer = nullptr;
        SDL_DestroyWindow( windowAndRenderer.window ); 
        windowAndRenderer.window = nullptr;

        // Quit SDL subsystems
        SDL_Quit();
    }

    void app::render()
    {
        if (pngTexture.isLoaded() == false)
        {
            SDL_Log("No Texture To Render!\n");
            return;
        }
        // Fill the background white
        SDL_SetRenderDrawColor(windowAndRenderer.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(windowAndRenderer.renderer);

        // Render image on screen
        pngTexture.render(windowAndRenderer.renderer, 0.f, 0.f);

        // Update screen
        SDL_RenderPresent(windowAndRenderer.renderer);
    }

    int app::getScreenWidth() const 
    { 
        return screenCfg.screenWidth;
    }

    int app::getScreenHeight() const 
    { 
        return screenCfg.screenHeight; 
    }

    SDL_Renderer* app::getRenderer() const
    {
        return windowAndRenderer.renderer;
    }

    SDL_Window* app::getWindow() const
    {
        return windowAndRenderer.window;
    }
}