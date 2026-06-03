/* Headers */
//Using SDL, SDL_image, and STL string
#include "core/App.hpp"
#include "core/Config.hpp"
#include "particles/Particle.hpp"
#include <SDL3/SDL_main.h>


int main(int argc, char* argv[])
{
    // Final Exit Code
    int exitCode{ 0 };

    // window and renderer 
    core::WindowAndRenderer wdrd;
    core::ScreenCfg cfg;

    // Create application instance
    core::App application(wdrd);
    
    // Initialize:
    if (application.init(cfg) == false)
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
            Particle p(application.getScreenWidth()/2, application.getScreenHeight()/2, 20, 10);
            // Create a draw object
            core::Color whiteColor{ 255, 255, 255, 255 }; // White color
            Uint64 previous = SDL_GetTicks();
        
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

                // State update: dt = 0.001
                Uint64 current = SDL_GetTicks();
                float velocity = 60;
                float dt = (current - previous) / 1000.0f;
                int width = application.getScreenWidth();
                if (p.getX() > ( width - 20 )) // bounce
                {
                    p.position.at(0) = (width - 20);
                    p.velocity.at(0) *= -0.8f;
                }
                p.position.at(0) += p.velocity.at(0) * dt;
                previous = current;

                // Render
                application.render_circle_with_dark_bckgrd(whiteColor, p);

        }
    }

    // Clean up
    application.close();

    return exitCode;
}