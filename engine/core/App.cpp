#include "core/App.hpp"
#include "rendering/DrawUtils.hpp"

namespace core
{
    bool App::init()
    {
        // Initialization Flag
        bool success{ true };
        
        if (SDL_Init(SDL_INIT_VIDEO) == false)
        {
            SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create Window with Renderer
            if (SDL_CreateWindowAndRenderer(
                "Particle Simulator", 
                screenCfg.screenWidth, 
                screenCfg.screenHeight,
                0,
                &windowAndRenderer.window,
                &windowAndRenderer.renderer
                ) == false
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
    
    bool App::loadBgAndFooMedia()
    {
        // File loading flag
        bool success{true};

        if (fooTexture.loadFromFile("./assets/foo.png", windowAndRenderer.renderer) == false)
        {
            SDL_Log("Unable to Load Foo Image!\n");
            success = false;
        }
        
        if (bgTexture.loadFromFile("./assets/background.png", windowAndRenderer.renderer) == false)
        {
            SDL_Log("Unable to Load Background Image!\n");
            success = false;
        }

        return success;
    }


    void App::close()
    {

        // Clean up Texture
        pngTexture.destroy();
        bgTexture.destroy();
        fooTexture.destroy();

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

    
    void App::beginFrame(Color& c)
    {
        setDrawColor(c);

        SDL_RenderClear(
            windowAndRenderer.renderer
        );
    }

    void App::drawParticle(
    Color& color,
    Particle& particle)
    {
        setDrawColor(color);

        rendering::drawCircle(
            windowAndRenderer.renderer,
            particle.getX(),
            particle.getY(),
            particle.getRadius()
        );
    }

    void App::endFrame()
    {
        SDL_RenderPresent(
            windowAndRenderer.renderer
        );
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
    
    void App::render_rectangle_with_dark_background(Color& color)
    {
        if (pngTexture.isLoaded() == true)
        {
            SDL_Log("There is aTexture To Render!\n");
            return;
        }
        // Fill the background black
        Color darkBckgrd{ 0, 0, 0, 255 };
        setDrawColor(darkBckgrd);
        SDL_RenderClear(windowAndRenderer.renderer);

        // circle
        setDrawColor(color);
        SDL_FRect box{
            600,
            300,
            100,
            100
        };

        SDL_RenderFillRect(
            windowAndRenderer.renderer,
            &box
        );

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

    rendering::Texture& App::getFooTexture()
    {
        return fooTexture;
    }

    rendering::Texture& App::getBgTexture()
    {
        return bgTexture;
    }

    void App::setDrawColor(Color& color)
    {
        SDL_SetRenderDrawColor(windowAndRenderer.renderer, color.r, color.g, color.b, color.a);
    }


}