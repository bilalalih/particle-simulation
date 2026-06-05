#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <vector>
#include "particles/Particle.hpp"
#include "rendering/ParticleRenderer.hpp"

namespace particles
{
    class ParticleSystem
    {
    public:
        ParticleSystem();

        void emit(float x, float y, int count);
        void update(float gravity, float floor, float dt);
        void render(rendering::ParticleRenderer& pRenderer);
        size_t count() const;

        private:
        std::vector<Particle> particles;

        void removeDead();
    };
}
#endif