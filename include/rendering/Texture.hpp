#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL3/SDL.h>
#include <string>

namespace rendering
{
    class Texture
    {
    public:
        // Symbolic constant
        static constexpr float kOriginalSize = -1.f;

        // Initializes texture variables
        Texture();

        // Cleans up texture variables
        ~Texture();

        Texture(const Texture& other);
        Texture(Texture&& other) noexcept;
        Texture& operator=(const Texture& other);
        Texture& operator=(Texture&& other) noexcept;

        // Cleans up texture
        void destroy();

        // Gets texture attributes
        int getWidth() const;
        int getHeight() const;
        bool isLoaded() const;

    private:
        // Contains texture data
        SDL_Texture* mTexture;
        SDL_Renderer* mRenderer;

        // Texture dimensions
        int mWidth;
        int mHeight;

        void copyFrom(const Texture& other);
        void swap(Texture& other) noexcept;
    };

}

#endif // TEXTURE_HPP