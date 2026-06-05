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

    void ParticleEmitter::update(float dt, ParticleSystem& system)
    {
        if (!active) return;

        accumulator += emissionRate * dt;

        while (accumulator >= 1)
        {
            system.emit(x, y, 1);
            accumulator -= 1;
        }
    }
}