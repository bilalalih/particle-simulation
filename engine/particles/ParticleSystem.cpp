#include "particles/ParticleSystem.hpp"

namespace particles
{
    ParticleSystem::ParticleSystem()
    {
        particles.reserve(10000);
    }

    void ParticleSystem::update(float floor, float dt)
    {
        for (auto& p : particles)
        {
            for (auto& force : forces)
            {
                force->apply(p, dt);
            }

            p.integrate(dt);
            p.floor(floor);
        }

        removeDead();
    }

    void ParticleSystem::addForce(std::unique_ptr<forces::Force> force)
    {
        forces.push_back(std::move(force));
    }

    const std::vector<Particle>& ParticleSystem::getParticles() const
    {
        return particles;
    }

    void ParticleSystem::removeDead()
    {
        size_t alive = 0;

        for (size_t i = 0; i < particles.size(); i++)
        {
            if (particles[i].getLife() > 0)
            {
                particles[alive++] = particles[i];
            }
        }

        particles.resize(alive);
    }

    void ParticleSystem::addParticle(const Particle& p)
    {
        particles.push_back(p);
    }

    size_t ParticleSystem::count() const
    {
        return particles.size();
    }
}