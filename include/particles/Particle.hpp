#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "math/Vec.hpp"

namespace particles
{
    class Particle
    {
    private:
        Vec2f position;
        Vec2f velocity;
        float radius = 4;
        float life = 0.f;

    public:
        Particle() noexcept;
        Particle(const Particle&) = default;
        Particle(Particle&&) noexcept = default;
        Particle& operator=(const Particle&) = default;
        Particle& operator=(Particle&&) noexcept = default;

        Particle(float x, float y, float vx, float vy);
        Particle(float x, float y, float vx, float vy, float radius);
        float getX() const;
        float getY() const;
        void addVelocity(float dx, float dy);
        void mulVelocity(float dx, float dy);
        void setVelocity(float vx, float vy);
        float getLife() const;
        void setLife(float life);
        void floor(float floor);
        void initRandomParticle(float mx, float my);
        void initRandP();
        void integrate(float dt);
        int getRadius() const;
    };
}

#endif // !PARTICLE_HPP