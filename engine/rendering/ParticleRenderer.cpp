#include "rendering/ParticleRenderer.hpp"

namespace rendering
{
    namespace
    {
        float clamp01(float value)
        {
            if (value < 0.0f) return 0.0f;
            if (value > 1.0f) return 1.0f;
            return value;
        }

        core::Color colorFor(float t, ParticleRenderer::Palette palette)
        {
            t = clamp01(t);

            switch (palette)
            {
                case ParticleRenderer::Palette::Rain:
                    return {
                        static_cast<Uint8>(80 + 90 * t),
                        static_cast<Uint8>(150 + 80 * t),
                        255,
                        static_cast<Uint8>(120 + 100 * t)
                    };

                case ParticleRenderer::Palette::Plasma:
                    return {
                        static_cast<Uint8>(90 + 165 * t),
                        static_cast<Uint8>(40 + 120 * (1.0f - t)),
                        static_cast<Uint8>(180 + 60 * t),
                        230
                    };

                case ParticleRenderer::Palette::Fire:
                default:
                    return {
                        255,
                        static_cast<Uint8>(80 + 175 * t),
                        static_cast<Uint8>(20 + 80 * t),
                        240
                    };
            }
        }
    }

    bool ParticleRenderer::init(SDL_Renderer* ren, float rad)
    {
        renderer = ren;
        radius  = rad;
        int size = static_cast<int>(radius * 2);

        texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            size,
            size
        );

        if (!texture) return false;

        if (!SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND))
        { 
            SDL_Log("Blend mode setup failed: %s", SDL_GetError());
        }

        SDL_Texture* previousTarget = SDL_GetRenderTarget(renderer);
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        int ir = static_cast<int>(radius);
        for (int y = -ir; y <= ir; y++)
        {
            for (int x = -ir; x <= ir; x++)
            {
                if (x*x + y*y <= ir*ir)
                {
                    SDL_RenderPoint(renderer, x + ir, y + ir);
                }
            }
        }

        SDL_SetRenderTarget(renderer, previousTarget);
        return true;
    }

    void ParticleRenderer::draw(const particles::Particle& p, const core::Color& color)
    {
        SDL_FRect dst{
            p.getX() - radius,
            p.getY() - radius,
            radius * 2.0f,
            radius * 2.0f
        };

        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(texture, color.a);
        if(!SDL_RenderTexture(renderer, texture, nullptr, &dst))
        {
            SDL_Log("Render failed: %s", SDL_GetError());
        }
    }

    void ParticleRenderer::drawAll(
        const std::vector<particles::Particle>& particles,
        Palette palette,
        float lifeScale
    )
    {
        for (auto& p : particles)
        {
            float t = p.getLife() / lifeScale;
            draw(p, colorFor(t, palette));
        }
    }

    void ParticleRenderer::destroy()
    {
        if(texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
}
