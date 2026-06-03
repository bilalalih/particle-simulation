/* Headers */
//Using SDL, SDL_image, and STL string
#include "core/Utils.hpp"
#include "core/Globals.hpp"
#include <SDL3/SDL_main.h>


int main(int argc, char* argv[])
{
    // Final Exit Code
    int exitCode{ 0 };

    // Create application instance
    core::app application(global::gWindowAndRenderer);
    
    // Initialize:
    if (application.init(global::gScreenCfg) == false)
    {
        SDL_Log("Unable To Initialize Program!\n");
        exitCode = 1;
    }
    else
    {
        // Load Media
        if (application.loadMedia("assets/loaded.png") == false)
        {
            SDL_Log("Unable To Load Media!\n");
            exitCode = 2;
        }
        else
        {
            // The quit flag
            bool quit{ false };

            // The event data
            SDL_Event(e);
            SDL_zero(e);
        
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
                application.render();
            }
        }
    }

    // Clean up
    application.close();

    return exitCode;
}