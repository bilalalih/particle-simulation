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
                // State update: dt = 0.001
                std::vector<Particle> particles;

                Uint64 current = SDL_GetTicks();
                    
                float velocity = 60;
                float dt = (current - previous) / 1000.0f;
                    
                int height = application.getScreenHeight();
                float gravity = 500;

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
                        newParticle.velocity.at(0) = 0;
                        application.render_circle_with_dark_bckgrd(whiteColor, newParticle);
                        particles.push_back( newParticle);
                    } else if (e.type == SDL_EVENT_QUIT)
                    {
                        // End the main loop
                        quit = true;
                    }
                }
                for ( auto& p : particles)
                {
                    if (p.getY() > ( height - 20 ) || p.getY() < 0 ) // bounce
                    {
                        p.position.at(1) = (height - 20);
                        p.velocity.at(1) *= -0.8f;
                    }
                    
                    p.velocity.at(1) += gravity * dt;
                    p.position.at(1) += p.velocity.at(1) * dt;
                    
                    // Render
                    application.render_circle_with_dark_bckgrd(whiteColor, p);
                }
                previous = current;
            }
        }
    // Clean up
    application.close();

    return exitCode;
}