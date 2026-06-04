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
    core::ScreenCfg cfg;

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
        if (application.loadFourMediaTextures() == false)
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

            // The currently rendered texture
            rendering::Texture* currentTexture = &application.getUpTexture();

            //Background color defaults to white
            core::Color bgColor{ 0xFF, 0xFF, 0xFF, 0xFF };

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

                    } // On keyboard key press
                    else if(e.type == SDL_EVENT_KEY_DOWN)
                    {
                        // Set Texture
                        if ( e.key.key == SDLK_UP )
                        {
                            currentTexture = &application.getUpTexture();
                        } 
                        else if ( e.key.key == SDLK_DOWN )
                        {
                            currentTexture = &application.getDownTexture();
                        } 
                        else if ( e.key.key == SDLK_LEFT )
                        {
                            currentTexture = &application.getLeftTexture();
                        } 
                        else if ( e.key.key == SDLK_RIGHT )
                        {
                            currentTexture = &application.getRightTexture();
                        }
                    }
                }

                // Reset background color to white
                bgColor.r = 0xFF;
                bgColor.g = 0XFF;
                bgColor.b = 0XFF;

                // Set backgroundcolor based on key state
                const bool* keyStates = SDL_GetKeyboardState( nullptr );
                if (keyStates[ SDL_SCANCODE_UP ] == true)
                {
                    // Red
                    bgColor.r = 0XFF;
                    bgColor.g = 0X00;
                    bgColor.b = 0X00;
                } 
                else if (keyStates[ SDL_SCANCODE_DOWN ] == true)
                {
                    // Green
                    bgColor.r = 0X00;
                    bgColor.g = 0XFF;
                    bgColor.b = 0X00;
                } 
                else if (keyStates[ SDL_SCANCODE_LEFT ] == true)
                {
                    // Yellow
                    bgColor.r = 0XFF;
                    bgColor.g = 0XFF;
                    bgColor.b = 0X00;
                } 
                else if (keyStates[ SDL_SCANCODE_RIGHT ] == true)
                {
                    // Blue
                    bgColor.r = 0X00;
                    bgColor.g = 0X00;
                    bgColor.b = 0XFF;
                }

                // Fill the background
                application.beginFrame(bgColor);

                // Render image on screen
                currentTexture->render(
                    application.getRenderer(), 
                    (application.getScreenWidth() - currentTexture->getWidth())/2.f,
                    (application.getScreenHeight() - currentTexture->getHeight())/2.f 
                ); 

                application.endFrame();
            } 
        }
    }
    // Clean up
    application.close();

    return exitCode;
}