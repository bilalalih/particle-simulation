#include <random>
#include <SDL3/SDL_log.h>
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

    void ParticleEmitter::setShape(std::unique_ptr<EmissionShape> s)
    {
        shape = std::move(s);
    }

    namespace {
        static std::mt19937& emitterRng()
        {
            static thread_local std::mt19937 rng(std::random_device{}());
            return rng;
        }

        static std::uniform_real_distribution<float> emitterAngleDist(-0.5f, 0.5f);
    }

    void ParticleEmitter::update(float dt, ParticleSystem& system)
    {
        if (!active) 
        {
            return;
        }

        accumulator += emissionRate * dt;

        while (accumulator >= 1.0f)
        {
            float x = position.x();
            float y = position.y();
            if (shape)
            {
                auto sampled = shape->sample();
                x = sampled.first;
                y = sampled.second;
            }

            Particle p(x, y, 0.0f, 0.0f);
            float angle = emitterAngleDist(emitterRng()) * spread;
            Vec2f particleVelocity = velocity;
            particleVelocity.x() += angle;
            p.setVelocity(particleVelocity);
            p.setLife(15.0f);
            system.addParticle(p);

            accumulator -= 1.0f;
        }
    }
}