#include "particles/ParticleEmitter.hpp"
#include "particles/ParticleSystem.hpp"

namespace particles
{
    ParticleEmitter::ParticleEmitter()
        : position{0.f, 0.f}
        , velocity{0.f, 0.f}
        , spread{0.f}
        , active(false)
        , emissionRate(100.f)
        , accumulator(0.f)
    {
    }

    void ParticleEmitter::setPosition(float px, float py)
    {
        position.x() = px;
        position.y() = py;
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
        velocity.x() = vx_;
        velocity.y() = vy_;
    }

    void ParticleEmitter::update(float dt, ParticleSystem& system)
    {
        if (!active) return;

        accumulator += emissionRate * dt;

        while (accumulator >= 1.0f)
        {
            Particle p(position.x(), position.y(), 0.0f, 0.0f);
            float angle = (rand() % 1000 / 1000.0f - 0.5f) * spread;
            Vec2f particleVelocity = velocity;
            particleVelocity.x() += angle;
            p.setVelocity(particleVelocity);
            p.setLife(15.0f);
            system.addParticle(p);

            accumulator -= 1.0f;
        }
    }
}