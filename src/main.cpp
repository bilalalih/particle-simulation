/* Headers */ 
//Using SDL, SDL_image, and STL string 
#include "core/App.hpp" 
#include "core/Config.hpp" 
#include "particles/Particle.hpp" 
#include "particles/ParticleSystem.hpp"
#include "rendering/ParticleRenderer.hpp"
#include "particles/ParticleEmitter.hpp"
#include "forces/GravityForce.hpp"
#include "forces/DragForce.hpp"
#include <cstdlib>
#include <algorithm>
#include <SDL3/SDL_main.h> 

int main(int argc, char* argv[]) { 
    
    // Final Exit Code 
    int exitCode{ 0 }; 
    
    // window and renderer 
    core::WindowAndRenderer wdrd; 
    core::ScreenCfg cfg; 
    
    // Create application instance 
    core::App application(wdrd, cfg); 
    
    // Initialize App: 
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
        particles::ParticleSystem particleSystem;
        
        particleSystem.addForce(std::make_unique<forces::GravityForce>(500));
        particleSystem.addForce(std::make_unique<forces::DragForce>(0.999f));
        
        rendering::ParticleRenderer particleRenderer;
        particleRenderer.init(application.getRenderer(), 8);

        particles::ParticleEmitter emitter;
        particles::ParticleEmitter fountain;

        fountain.setPosition(50,50);
        fountain.setRate(400);
        fountain.setVelocity(0, -500);
        fountain.setSpread(300);

        fountain.start();

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
            dt = std::min(dt, 0.016f);
            previous = current;

            // Get event data 
             while (SDL_PollEvent( &e ) == true) 
             { 
                if ( e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
                { 
                    emitter.setPosition(e.button.x, e.button.y);
                    emitter.start();
                } 
                if (e.type == SDL_EVENT_MOUSE_BUTTON_UP)
                {
                    emitter.stop();
                }
                if (e.type == SDL_EVENT_MOUSE_MOTION)
                {
                    emitter.setPosition(e.button.x, e.button.y);
                }
                else if (e.type == SDL_EVENT_QUIT) 
                { 
                    // End the main loop 
                    quit = true; 
                } 
            } 
            
            // Creates a Frame 
            application.beginFrame();
            
            // emit
            emitter.update(dt, particleSystem);
            fountain.update(dt, particleSystem);

            // Update state 
            particleSystem.update(height, dt);

            // Render image
            particleRenderer.drawAll(particleSystem.getParticles());
            
            // Update the screen using our Frame
            application.endFrame();

            
            // FPS timer, it logs our FPS Rate to my terminal.
            // the condition (fpsTimer > 1) means we render the FPS only after a second
            static float fpsTimer = 0;
            static int frames = 0;
            fpsTimer += dt;
            frames++;

            if(fpsTimer>1)
            {
                SDL_Log("FPS: %d", frames);
                frames=0;
                fpsTimer=0;
            }

           static float timer = 0.f;
           timer += dt;
           if (timer > 1.0f)
           {
                SDL_Log("Particles: %zu",particleSystem.count());
                timer = 0;
           }
           
        } 
        particleRenderer.destroy();
    } 

    // Clean up
    application.close(); 
    return exitCode; 
}