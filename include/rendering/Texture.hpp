#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL3/SDL.h>
#include <string>

namespace rendering
{
    class Texture
    {
    public:
        // Initializes texture variables
        Texture();

        // Cleans up texture variables
        ~Texture();

        // Remove copy constructor
        Texture( const Texture& ) = delete;

        // Remove copy assignment
        Texture& operator=( const Texture& ) = delete;

        // Remove move constructor
        Texture( Texture&& ) = delete;

        // Remove move assignment
        Texture& operator=( Texture&& ) = delete;

        // Loads texture from disk
        bool loadFromFile(const std::string& path, SDL_Renderer* renderer);

        // Cleans up texture
        void destroy();

        // Draws texture
        void render(SDL_Renderer* renderer, float x, float y);

        // Gets texture attributes
        int getWidth() const;
        int getHeight() const;
        bool isLoaded() const;

    private:
        // Contains texture data
        SDL_Texture* mTexture;

        // Texture dimensions
        int mWidth;
        int mHeight;
    };

}

#endif // TEXTURE_HPP