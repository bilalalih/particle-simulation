#include <SDL3/SDL.h>
#include <iostream>

/* Constants */
// Screen dimension constants
constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 800 };

/* Function Prototypes */
// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees Media and shutdowns SDL
void close();

/* Global Variables */
// The window we'll be rendering to
SDL_Window* gWindow{nullptr};

// The surface contained by the window
SDL_Surface* gScreenSurface{nullptr};

// The image we will load and show on the screen
SDL_Surface* gScene{ nullptr };

bool init()
{
    // Initialization Flag
    bool success{ true };
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log("SDL could not initialize! SDL Error: %s/n", SDL_GetError());
        return -1;
    }

}


int main(int argc, char* argv[])
{
    
    std::cout << "SDL initialized successfully!" << std::endl;
    SDL_Window* window = SDL_CreateWindow(
        "Particle Simulator",
        800,
        600,
        0
    );

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}