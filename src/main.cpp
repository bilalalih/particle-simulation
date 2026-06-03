/* Headers */
//Using SDL, SDL_image, and STL string
#include "core/Utils.hpp"
#include "core/Globals.hpp"
#include "particles/Particle.hpp"
#include <SDL3/SDL_main.h>


int main(int argc, char* argv[])
{
    // Final Exit Code
    int exitCode{ 0 };

    // Create application instance
    core::App application(global::gWindowAndRenderer);
    
    // Initialize:
    if (application.init(global::gScreenCfg) == false)
    {
        SDL_Log("Unable To Initialize Program!\n");
        exitCode = 1;
    }
    else
    {
            // The quit flag
            bool quit{ false };

            // The event data
            SDL_Event(e);
            SDL_zero(e);

            // Create a particle
            Particle p(application.getScreenWidth()/2, application.getScreenHeight()/2);
            // Create a draw object
            core::Color whiteColor{ 255, 255, 255, 255 }; // White color
        
            // The main loop
            while (quit == false)
            {
                // Get event data
                while (SDL_PollEvent( &e ) == true)
                {
                    // if event is quit type
                    if (e.type == SDL_EVENT_QUIT)
                    {
                        // End the main loop
                        quit = true;
                    }
                }

                // Render
                application.render_rectangle_with_dark_background(whiteColor);
        }
    }

    // Clean up
    application.close();

    return exitCode;
}