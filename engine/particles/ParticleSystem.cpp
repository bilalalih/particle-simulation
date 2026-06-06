#include "particles/ParticleSystem.hpp"
#include <algorithm>

namespace particles
{
    ParticleSystem::ParticleSystem()
    {
        particles.reserve(10000);
    }

    void ParticleSystem::emit(float x, float y, int count)
    {
        for(int i = 0; i < count; i++)
        {
            Particle p;
            p.initRandomParticle(x, y);
            addParticle(p);
        }
    }

    void ParticleSystem::resolveFloor(Particle& p, float f)
    {
        if (p.getY() + p.getRadius() > f)
        {
            p.setY(f - p.getRadius());
            p.setVY(-0.8f * p.getVY());
        }
    }

    void ParticleSystem::update(float floor, float dt)
    {
        for (auto& p : particles)
        {
            for (auto& force : forces)
            {
                force->apply(p);
            }

            p.integrate(dt);
            resolveFloor(p, floor);
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
        particles.erase(
            std::remove_if(
                particles.begin(),
                particles.end(),
                [](const Particle& particle) {
                    return particle.getLife() <= 0.0f;
                }
            ),
            particles.end()
        );
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