/* Headers */
//Using SDL, SDL_image, and STL string
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>

/* Constants */
namespace screenConstants
{
    // Screen dimension constants
    constexpr int kScreenWidth{ 640 };
    constexpr int kScreenHeight{ 800 };
};

/* Global Variables */
namespace global
{
    // The window we'll be rendering to
    SDL_Window* gWindow{ nullptr };

    // The surface contained by the window
    SDL_Renderer* gRenderer{ nullptr };

    // The PNG image we will render
    LTexture gPngTexture;
}

/* Function Prototypes */
// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees Media and shutdowns SDL
void close();

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
        // Create Window with Renderer
        if (SDL_CreateWindowAndRenderer(
            "Particle SImulation: Texture And Extension Libraries", 
            screenConstants::kScreenWidth, 
            screenConstants::kScreenHeight,
            0,
            &global::gWindow,
            &global::gRenderer
            ) == false
        ){
            SDL_Log("Window Could Not Be Created! SDL Error: %s/n", SDL_GetError());
            success = false;
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
    if (global::gPngTexture.loadFromFile("assets/loaded.png") == false)
    {
        SDL_Log("Unable To Load PNG Image!\n");
        success = false;
    }

    return success;
}

void close()
{

    // Clean up Texture
    global::gPngTexture.destroy();

    // Destroy Window
    SDL_DestroyRenderer( global::gRenderer );
    global::gRenderer = nullptr;
    SDL_DestroyWindow( global::gWindow ); 
    global::gWindow = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

/* Class Prototypes */
class LTexture
{
public:
    // Initializes texture variables
    LTexture();

    // Cleans up texture variables
    ~LTexture();

    // Loads texture from disk
    bool loadFromFile(const std::string& path);

    // Cleans up texture
    void destroy();

    // Draws texture
    void render(float x, float y);

    // Gets texture attributes
    int getWidth();
    int getHeight();
    bool isLoaded();

private:
    // Contains texture data
    SDL_Texture* mTexture;

    // Texture dimeensions
    int mWidth;
    int mHeight;
};

/* Class Implementations */
// LTexture implementation
LTexture::LTexture()
:
    // Initialize texture variables
    mTexture( nullptr ),
    mWidth(0),
    mHeight(0)
{

}

LTexture::~LTexture()
{
    // Clean up texture
    destroy();
}

bool LTexture::loadFromFile(const std::string& path)
{
    // Clean up texture if it already exists
    destroy();

    // Load surface
    if (SDL_Surface* LoadedSurface = IMG_Load( path.c_str() ); LoadedSurface == nullptr)
    {
        SDL_Log("Unable To Load Image %s! SDL error: %s/n", path.c_str(), SDL_GetError());
        return false;
    }
    else
    {
        // Create texture from surface
        
        SDL_Surface* loadedSurface{ SDL_LoadPNG( path.c_str()) };
        if (loadedSurface == nullptr)
        {
            SDL_Log("Unable To Load Image %s! SDL error: %s/n ", path.c_str(), SDL_GetError());
        } else
        {
            // Create texture from surface pixels
            if (mTexture = SDL_CreateTextureFromSurface(global::gRenderer, loadedSurface); mTexture == nullptr)
            {
                SDL_Log("Unable To Create Texture From %s! SDL error: %s/n ",path.c_str(), SDL_GetError());
            } else
            {
                // Get image dimensions
                mWidth = loadedSurface->w;
                mHeight = loadedSurface->h;
            }
        }
        
        // Clean up loaded surface
        SDL_DestroySurface( loadedSurface );
    }
    
    // Return success if texture loaded
    return mTexture != nullptr;
}

void LTexture::destroy()
{
    // Clean up texture
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture( mTexture );
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(float x, float y)
{
    // Set texture position
    SDL_FRect dstRect{x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};

    // Render texture
    SDL_RenderTexture(global::gRenderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool LTexture::isLoaded()
{
    return mTexture != nullptr;
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

                // Fill the background white
                SDL_SetRenderDrawColor(global::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(global::gRenderer);

                // Render image on screen
                global::gPngTexture.render(0.f, 0.f);

                // Update screen
                SDL_RenderPresent(global::gRenderer);
            }
        }
    }

    // Clean up
    close();

    return exitCode;
}