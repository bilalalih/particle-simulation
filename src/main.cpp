//main.cpp 
/* Headers */ 
//Using SDL, SDL_image, and STL string 
#include "core/App.hpp" 
#include "core/Config.hpp" 
#include "particles/Particle.hpp" 
#include "rendering/ParticleRenderer.hpp"
#include <cstdlib>
#include <SDL3/SDL_main.h> 
int main(int argc, char* argv[]) { 
    // Final Exit Code 
    int exitCode{ 0 }; 
    // window and renderer 
    core::WindowAndRenderer wdrd; 
    core::ScreenCfg cfg; 
    
    // Create application instance 
    core::App application(wdrd, cfg); 
    
    // Initialize: 
    if (application.init() == false) 
    { SDL_Log("Unable To Initialize Program!\n"); 
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
        particles.reserve(10000);
        
        rendering::ParticleRenderer particleRenderer;
        particleRenderer.init(application.getRenderer(), 8);

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

            static float fpsTimer = 0;
            static int frames = 0;
            fpsTimer += dt;
            frames++;

            if(fpsTimer>1)
            {
                SDL_Log(
                    "FPS: %d",
                    frames
                );

                frames=0;

                fpsTimer=0;
            }

            // Get event data 
             while (SDL_PollEvent( &e ) == true) 
             { 
                if ( e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
                { 
                    float mx = e.button.x; 
                    float my = e.button.y; 
                    Particle p(mx, my, 0, 0); 
                    for(int i = 0; i<50; i++)
                    {
                        Particle p(mx,my,0,0);
                        p.initRandomParticle(mx, my);
                        particles.push_back(p);
                    } 
                } 
                else if (e.type == SDL_EVENT_QUIT) 
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
                    float t = p.getLife() / 15.0f;
                    core::Color c;
                    c.r = 255;
                    c.g = 255 * t;
                    c.b = 255 * t;
                    c.a = 255;
                    p.update(gravity, height, dt);

                    particleRenderer.draw(p, c);
                }
                application.endFrame();

                size_t alive = 0;
                for (size_t i = 0; i < particles.size(); i++)
                {
                    if (particles[i].getLife() > 0)
                    {
                        particles[alive++] = particles[i];
                    }
                } 

                particles.resize(alive);
            }
            else
            {
                application.endFrame();
            }
            
            static float timer = 0;

            timer += dt;
            if (timer > 1.0f)
            {
                SDL_Log("Particles: %d", particles.size());
                timer = 0;
            }
        } 
        particleRenderer.destroy();
    } 

    // Clean up
    application.close(); 
    return exitCode; 
}