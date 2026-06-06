#include <random>
#include <cmath>
#include <SDL3/SDL_log.h>
#include "particles/ParticleEmitter.hpp"
#include "particles/ParticleSystem.hpp"

namespace particles
{
    ParticleEmitter::ParticleEmitter()
        : position{0.f, 0.f}
        , velocity{0.f, 0.f}
        , spread{0.f}
        , particleLife(15.f)
        , particleRadius(4.f)
        , active(false)
        , emissionRate(100.f)
        , accumulator(0.f)
    {
    }

    void ParticleEmitter::setPosition(float px, float py)
    {
        position.x() = px;
        position.y() = py;

        if (shape)
        {
            shape->setPosition(px, py);
        }
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

    void ParticleEmitter::setParticleLife(float seconds)
    {
        particleLife = seconds;
    }

    void ParticleEmitter::setParticleRadius(float radius)
    {
        particleRadius = radius;
    }

    void ParticleEmitter::setVelocity(float vx_, float vy_)
    {
        velocity.x() = vx_;
        velocity.y() = vy_;
    }

    void ParticleEmitter::setShape(std::unique_ptr<EmissionShape> s)
    {
        shape = std::move(s);

        if (shape)
        {
            shape->setPosition(position.x(), position.y());
        }
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

            Particle p(x, y, 0.0f, 0.0f, particleRadius);
            float angle = emitterAngleDist(emitterRng()) * spread * 0.0174532925f;
            Vec2f particleVelocity = velocity;
            if (spread != 0.0f)
            {
                float cs = std::cos(angle);
                float sn = std::sin(angle);
                particleVelocity = {
                    velocity.x() * cs - velocity.y() * sn,
                    velocity.x() * sn + velocity.y() * cs
                };
            }
            p.setVelocity(particleVelocity);
            p.setLife(particleLife);
            system.addParticle(p);

            accumulator -= 1.0f;
        }
    }
}
