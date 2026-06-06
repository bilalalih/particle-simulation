#ifndef PARTICLE_RENDERER_HPP
#define PARTICLE_RENDERER_HPP

#include <SDL3/SDL.h>
#include <vector>
#include "core/Config.hpp"
#include "particles/Particle.hpp"

namespace rendering
{
    class ParticleRenderer
    {
    public:
        enum class Palette
        {
            Fire,
            Rain,
            Plasma
        };

        bool init(SDL_Renderer* ren, float rad);
        void draw(const particles::Particle& p, const core::Color& color);
        void drawAll(
            const std::vector<particles::Particle>& particles,
            Palette palette = Palette::Fire,
            float lifeScale = 15.0f
        );
        void destroy();
        
    private:
        SDL_Renderer* renderer {};
        SDL_Texture* texture {};
        float radius {};
    };
}

#endif
