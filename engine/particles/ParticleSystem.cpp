#include "particles/ParticleSystem.hpp"

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
            Particle p(x, y, 0.f, 0.f);
            p.initRandomParticle(x, y);
            particles.push_back(p);
        }
    }

    void ParticleSystem::update(float gravity, float floor, float dt)
    {
        for (auto& p : particles)
        {
            p.update(gravity, floor, dt);
        }

        removeDead();
    }

    void ParticleSystem::render(rendering::ParticleRenderer& pRenderer)
    {
        for (auto& p : particles)
        {
            float t = p.getLife() / 15.0f;
            
            core::Color c;
            c.r = 255;
            c.g = 255 * t;
            c.b = 255 * t;
            c.a = 255;

            pRenderer.draw(p, c);
        }
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

    size_t ParticleSystem::count() const
    {
        return particles.size();
    }
}