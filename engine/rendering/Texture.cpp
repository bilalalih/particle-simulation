#include "rendering/Texture.hpp"
#include <SDL3_image/SDL_image.h>
#include <utility>

namespace rendering
{
    Texture::Texture()
    :
        mTexture(nullptr),
        mRenderer(nullptr),
        mWidth(0),
        mHeight(0)
    {
    }

    Texture::Texture(const Texture& other)
    : mTexture(nullptr), mRenderer(nullptr), mWidth(0), mHeight(0)
    {
        copyFrom(other);
    }

    Texture::Texture(Texture&& other) noexcept
    : mTexture(other.mTexture), mRenderer(other.mRenderer), mWidth(other.mWidth), mHeight(other.mHeight)
    {
        other.mTexture = nullptr;
        other.mRenderer = nullptr;
        other.mWidth = 0;
        other.mHeight = 0;
    }

    Texture& Texture::operator=(const Texture& other)
    {
        if (this != &other)
        {
            Texture copy(other);
            swap(copy);
        }
        return *this;
    }

    Texture& Texture::operator=(Texture&& other) noexcept
    {
        if (this != &other)
        {
            destroy();
            mTexture = other.mTexture;
            mRenderer = other.mRenderer;
            mWidth = other.mWidth;
            mHeight = other.mHeight;

            other.mTexture = nullptr;
            other.mRenderer = nullptr;
            other.mWidth = 0;
            other.mHeight = 0;
        }
        return *this;
    }

    void Texture::swap(Texture& other) noexcept
    {
        std::swap(mTexture, other.mTexture);
        std::swap(mRenderer, other.mRenderer);
        std::swap(mWidth, other.mWidth);
        std::swap(mHeight, other.mHeight);
    }

    void Texture::copyFrom(const Texture& other)
    {
        if (other.mTexture == nullptr || other.mRenderer == nullptr)
        {
            return;
        }

        float width;
        float height;
        if (!SDL_GetTextureSize(other.mTexture, &width, &height))
        {
            return;
        }

        mRenderer = other.mRenderer;
        mWidth = static_cast<int>(width);
        mHeight = static_cast<int>(height);

        mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);
        if (mTexture == nullptr)
        {
            mRenderer = nullptr;
            mWidth = 0;
            mHeight = 0;
            return;
        }

        SDL_Texture* previousTarget = SDL_GetRenderTarget(mRenderer);
        SDL_SetRenderTarget(mRenderer, mTexture);
        SDL_RenderTexture(mRenderer, other.mTexture, nullptr, nullptr);
        SDL_SetRenderTarget(mRenderer, previousTarget);

        SDL_BlendMode blendMode;
        if (SDL_GetTextureBlendMode(other.mTexture, &blendMode) == 0)
        {
            SDL_SetTextureBlendMode(mTexture, blendMode);
        }
    }

    Texture::~Texture()
    {
        // Clean up texture
        destroy();
    }

    void Texture::destroy()
    {
        // Clean up texture
        if (mTexture != nullptr)
        {
            SDL_DestroyTexture( mTexture );
            mTexture = nullptr;
        }
        mRenderer = nullptr;
        mWidth = 0;
        mHeight = 0;
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