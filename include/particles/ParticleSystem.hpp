#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <vector>
#include <memory>
#include "particles/Particle.hpp"
#include "forces/Force.hpp"
#include "rendering/ParticleRenderer.hpp"

namespace particles
{
    class ParticleSystem
    {
    public:
        ParticleSystem();

        void emit(float x, float y, int count);
        void resolveFloor(Particle& p, float floor);
        void update(float floor, float dt);
        void addForce(std::unique_ptr<forces::Force> force);
        size_t count() const;
        const std::vector<Particle>& getParticles() const;
        void addParticle(const Particle& particle);

        private:
        std::vector<Particle> particles;
        std::vector<std::unique_ptr<forces::Force>> forces;

        void removeDead();
    };
}
#endif