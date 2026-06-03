#include "core/Utils.hpp"
#include "rendering/DrawUtils.hpp"

namespace core
{
    bool App::init(const ScreenCfg& screenCfg_)
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
                "Particle Simulation: Texture And Extension Libraries", 
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

    bool App::loadMedia(const std::string& path)
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

    void App::close()
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

    void App::render_circle_with_dark_bckgrd(Color& color, Particle& particle, int radius)
    {
        if (pngTexture.isLoaded() == true)
        {
            SDL_Log("There is aTexture To Render!\n");
            return;
        }
        // Fill the background black
        Color darkBckgrd{ 20, 20, 30, 255 };
        setDrawColor(darkBckgrd);
        SDL_RenderClear(windowAndRenderer.renderer);

        // circle
        setDrawColor(color);
        rendering::drawCircle(windowAndRenderer.renderer, particle.getX(), particle.getY(), radius);

        // Update screen
        SDL_RenderPresent(windowAndRenderer.renderer);
    }

    void App::render_img(Color& color)
    {
        if (pngTexture.isLoaded() == false)
        {
            SDL_Log("No Texture To Render!\n");
            return;
        }
        // Fill the background 
        setDrawColor(color);
        SDL_RenderClear(windowAndRenderer.renderer);

        // Render image on screen
        pngTexture.render(windowAndRenderer.renderer, 0.f, 0.f);

        // Update screen
        SDL_RenderPresent(windowAndRenderer.renderer);
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

    void App::setDrawColor(Color& color)
    {
        SDL_SetRenderDrawColor(windowAndRenderer.renderer, color.r, color.g, color.b, color.a);
    }
}