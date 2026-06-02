#include <SDL3/SDL.h>
#include <string>

/* Constants */
namespace screenConstants
{
    // Screen dimension constants
    constexpr int kScreenWidth{ 640 };
    constexpr int kScreenHeight{ 800 };
};

/* Function Prototypes */
// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees Media and shutdowns SDL
void close();

/* Global Variables */
namespace global
{
    // The window we'll be rendering to
    SDL_Window* gWindow{ nullptr };

    // The surface contained by the window
    SDL_Surface* gScreenSurface{ nullptr };

    // The image we will load and show on the screen
    SDL_Surface* gScene{ nullptr };
}

bool init()
{
    // Initialization Flag
    bool success{ true };
    
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log("SDL could not initialize! SDL Error: %s/n", SDL_GetError());
        success = false;
    } else 
    {
        // Create Window
        if (global::gWindow = SDL_CreateWindow(
            "Particle SImulation: Hello SDL3", 
            screenConstants::kScreenWidth, 
            screenConstants::kScreenHeight,
            0
            ); 
            global::gWindow == nullptr
        ){
            SDL_Log("Window Could Not Be Created! SDL Error: %s/n", SDL_GetError());
            success = false;
        } else
        {
            // Get Window Surface
            global::gScreenSurface = SDL_GetWindowSurface(global::gWindow);
        }
    }

    SDL_Log("SDL Initialized Succesfully");
    return success;
}

bool loadMedia()
{
    // File loading flag
    bool success{ true };

    // Load splash image
    std::string imagePath{"image.png"};
    if (global::gScene = SDL_LoadPNG( imagePath.c_str()); global::gScene == nullptr)
    {
        SDL_Log("Unable To Load Image %s! SDL error: %s/n ",imagePath.c_str(), SDL_GetError());
        success = false;
    }

    return success;
}

void close()
{
    // Clean up Surface
    SDL_DestroySurface( global::gScene );
    global::gScene = nullptr;

    // Destroy Window
    SDL_DestroyWindow( global::gWindow ); 
    global::gWindow = nullptr;
    global::gScreenSurface = nullptr;

    // Quit SDL subsystems
    SDL_Delay(100);
    SDL_Quit();
}


int main(int argc, char* argv[])
{
    // Final Exit Code
    int exitCode{ 0 };
    
    // Initialize:
    if (init() == false)
    {
        SDL_Log("Unable To Initialize Program!\n");
        exitCode = 1;
    }
    else
    {
        // Load Media
        if (loadMedia() == false)
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

                // Fill the surface white
                SDL_FillSurfaceRect(global::gScreenSurface, nullptr, SDL_MapSurfaceRGB(global::gScreenSurface, 0xFF, 0xFF, 0xFF));

                // Render image on screen
                SDL_BlitSurface(global::gScene, nullptr, global::gScreenSurface, nullptr);

                // Update the surface
                SDL_UpdateWindowSurface( global::gWindow );
                
            }
        }
    }

    // Clean up
    close();

    return exitCode;
}