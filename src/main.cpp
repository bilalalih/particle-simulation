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
        if (application.loadMedia("assets/dots.png") == false)
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

            // Sprite image
            rendering::Texture* spriteSheetTexture = &application.getSpriteSheetTexture();

            //Background color defaults to white
            core::Color whiteColor{ 0xFF, 0xFF, 0xFF, 0xFF };
            const float width = application.getScreenWidth();
            const float height = application.getScreenHeight();

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

                // Fill the background white
                application.beginFrame(whiteColor);

                // Init sprite clip
                constexpr float kSpriteSize = 100.f;
                SDL_FRect spriteClip{0.f, 0.f, kSpriteSize, kSpriteSize};

                // Init sprite size
                SDL_FRect spriteSize{0.f, 0.f, kSpriteSize, kSpriteSize};

                // Use top left sprite
                spriteClip.x = 0.f;
                spriteClip.y = 0.f;

                // Set sprite size to original size
                spriteSize.w = kSpriteSize;
                spriteSize.h = kSpriteSize;

                // Draw original sized sprite
                spriteSheetTexture->render_rect(0.f, 0.f, &spriteClip, spriteSize.w, spriteSize.h, application.getRenderer());

                // Use top right sprite
                spriteClip.x = kSpriteSize;
                spriteClip.y =        0.f;

                // Set sprite to half size
                spriteSize.w = kSpriteSize * 0.5f;
                spriteSize.h = kSpriteSize * 0.5f;

                // Draw half size sprite
                spriteSheetTexture->render_rect(width - spriteSize.w, 0.f, &spriteClip, spriteSize.w, spriteSize.h, application.getRenderer());

                // Use bottom left sprite
                spriteClip.x = 0.f;
                spriteClip.y = kSpriteSize;

                // Set sprite to double size
                spriteSize.w = kSpriteSize * 2.f;
                spriteSize.h = kSpriteSize * 2.f;

                // Draw double size sprite
                spriteSheetTexture->render_rect(0.f, height - spriteSize.h, &spriteClip, spriteSize.w, spriteSize.h, application.getRenderer());

                // Use bottom right sprite
                spriteClip.x = kSpriteSize;
                spriteClip.y = kSpriteSize;

                // Squish the sprite vertically
                spriteSize.w = kSpriteSize;
                spriteSize.h = kSpriteSize * 0.5f;

                // Draw double size sprite
                spriteSheetTexture->render_rect(width - spriteSize.w, height - spriteSize.h, &spriteClip, spriteSize.w, spriteSize.h, application.getRenderer());
                
                application.endFrame();
            } 
        }
    }
    // Clean up
    application.close();

    return exitCode;
}