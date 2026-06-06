#ifndef PARTICLE_EMITTER_HPP
#define PARTICLE_EMITTER_HPP

#include <memory>
#include "math/Vec.hpp"
#include "particles/shapes/EmissionShape.hpp"

namespace particles
{
    class ParticleSystem;

    class ParticleEmitter
    {
    public:
        ParticleEmitter();

        void setPosition(float px, float py);
        void start();
        void stop();
        void setRate(float rate);
        void setVelocity(float vx, float vy);
        void setSpread(float degrees);
        void setParticleLife(float seconds);
        void setParticleRadius(float radius);
        void setShape(std::unique_ptr<EmissionShape> s);

        void update(float dt, ParticleSystem& system);

    private:
        std::unique_ptr<EmissionShape> shape;
        Vec2f position{};
        Vec2f velocity{};

        float spread{0};
        float particleLife{15.0f};
        float particleRadius{4.0f};
        bool active{false};
        float emissionRate{100};
        float accumulator{0.0f};
    };
    
}
#endif
