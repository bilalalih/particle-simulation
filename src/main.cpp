/* Headers */
//Using SDL, SDL_image, and STL string
#include "core/App.hpp"
#include "core/Config.hpp"
#include "particles/Particle.hpp"
#include "rendering/Texture.hpp"
#include <SDL3/SDL_main.h>


int main(int argc, char* argv[])
{
    // Final Exit Code
    int exitCode{ 0 };

    // window and renderer 
    core::WindowAndRenderer wdrd;
    core::ScreenCfg cfg{640, 480};

    // Create application instance
    core::App application(wdrd, cfg);
    
    // Initialize:
    if (application.init() == false)
    {
        SDL_Log("Unable To Initialize Program!\n");
        exitCode = 1;
    }
    else
    {
        // Load Media
        if (application.loadBgAndFooMedia() == false)
        {
            SDL_Log("Unable To Load Media!\n");
            exitCode = 2;
        } 
        else
        {
            // The quit flag
            bool quit{ false };

            // The event data
            SDL_Event e;
            SDL_zero(e);

            // The background and charcter image
            rendering::Texture* bgTexture = &application.getBgTexture();
            rendering::Texture* fooTexture = &application.getFooTexture();

            //Background color defaults to white
            core::Color whiteColor{ 0xFF, 0xFF, 0xFF, 0xFF };

            // The main loop
            while (quit == false)
            {
                // Get event data
                while( SDL_PollEvent(&e) == true )
                {
                    // If event is quit type
                    if (e.type == SDL_EVENT_QUIT)
                    {
                        // End the main loop
                        quit = true;

                    }
                }

                // Fill the background
                application.beginFrame(whiteColor);

                // Render background image on screen
                bgTexture->render(
                    application.getRenderer(), 
                    0.f,
                    0.f 
                ); 
                
                fooTexture->render(
                    application.getRenderer(), 
                    240.f,
                    190.f 
                ); 

                application.endFrame();
            } 
        }
    }
    // Clean up
    application.close();

    return exitCode;
}