#include "rendering/ParticleRenderer.hpp"

namespace rendering
{
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

        SDL_SetRenderTarget(renderer, nullptr);
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

        SDL_RenderTexture(renderer, texture, nullptr, &dst);
    }

    void ParticleRenderer::drawAll(const std::vector<particles::Particle>& particles)
    {
        for (auto& p : particles)
        {
            float t = p.getLife() / 15.0f;
            
            core::Color c;
            c.r = 255;
            c.g = 255 * t;
            c.b = 255 * t;
            c.a = 255;

            draw(p, c);
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