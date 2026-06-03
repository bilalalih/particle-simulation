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

            // Create an empty particle space
            std::vector<Particle> particles;

            // color object
            core::Color whiteColor{ 255, 255, 255, 255 }; // White color
            
            Uint64 previous = SDL_GetTicks();

            int height = application.getScreenHeight();
            float gravity = 500;
        
            // The main loop
            while (quit == false)
            {

                Uint64 current = SDL_GetTicks();    
                float dt = (current - previous) / 1000.0f;
                previous = current;

                // Get event data
                while (SDL_PollEvent( &e ) == true)
                {                    
                    if ( e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
                    {
                        float mx = e.button.x; 
                        float my = e.button.y;
                        
                        Particle newParticle(0, 0, 0, 0);
                        newParticle.position.at(0) = mx;
                        newParticle.position.at(1) = my;
                        newParticle.velocity.at(0) = 0;
                        newParticle.velocity.at(1) = 0;
                        particles.push_back( newParticle);
                    } else if (e.type == SDL_EVENT_QUIT)
                    {
                        // End the main loop
                        quit = true;
                    }
                }

                application.beginFrame();
                // update state
                if (!particles.empty())
                {
                    for (auto& p : particles)
                    {
                        p.velocity.at(1) += gravity * dt;

                        p.position.at(0) += p.velocity.at(0) * dt;
                        p.position.at(1) += p.velocity.at(1) * dt ;

                        application.drawParticle(whiteColor, p);
                    }
                }
                application.endFrame();
            }
        }
    // Clean up
    application.close();

    return exitCode;
}