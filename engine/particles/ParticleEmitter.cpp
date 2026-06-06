#include "particles/ParticleEmitter.hpp"
#include "particles/ParticleSystem.hpp"

namespace particles
{
    void ParticleEmitter::setPosition(float px, float py)
    {
        x = px;
        y = py;
    }

    void ParticleEmitter::start()
    {
        active = true;
    }

    void ParticleEmitter::stop()
    {
        active = false;
    }

    void ParticleEmitter::setRate(float r)
    {
        emissionRate = r;
    }

    void ParticleEmitter::setSpread(float d)
    {
        spread = d;
    } 

    void ParticleEmitter::setVelocity(float vx_, float vy_)
    {
        vx = vx_;
        vy = vy_;
    }

    void ParticleEmitter::update(float dt, ParticleSystem& system)
    {
        if (!active) return;

        accumulator += emissionRate * dt;

        while (accumulator >= 1)
        {
            Particle p(x, y, 0, 0);
            float offset = (rand()%1000 / 1000.0f - 0.5f) * spread;
            p.setVelocity(float(vx + offset), float(vy + offset));
            p.setLife(15);
            system.addParticle(p);

            accumulator--;
        }
    }
}