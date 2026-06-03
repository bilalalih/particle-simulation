#include "rendering/Texture.hpp"
#include <SDL3_image/SDL_image.h>

namespace rendering
{
    Texture::Texture()
    :
        // Initialize texture variables
        mTexture( nullptr ),
        mWidth(0),
        mHeight(0)
    {

    }

    Texture::~Texture()
    {
        // Clean up texture
        destroy();
    }

    bool Texture::loadFromFile(const std::string& path, SDL_Renderer* renderer)
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
                if (mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); mTexture == nullptr)
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

    void Texture::destroy()
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

    void Texture::render(SDL_Renderer* renderer, float x, float y)
    {
        // Set texture position
        SDL_FRect dstRect{x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};

        // Render texture
        SDL_RenderTexture(renderer, mTexture, nullptr, &dstRect);
    }

    int Texture::getWidth() const
    {
        return mWidth;
    }

    int Texture::getHeight() const
    {
        return mHeight;
    }

    bool Texture::isLoaded() const
    {
        return mTexture != nullptr;
    }
}