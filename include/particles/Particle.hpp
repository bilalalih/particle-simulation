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
        Vec2f acceleration;
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
        float getVX() const;
        float getVY() const;
        const Vec2f& getPosition() const;
        const Vec2f& getVelocity() const;
        void setX(float x);
        void setY(float y);
        void setPosition(float x, float y);
        void setVY(float vy);
        void setVX(float vx);
        void addVelocity(float dx, float dy);
        void addVelocity(const Vec2f& dv);
        void mulVelocity(float dx, float dy);
        void mulVelocity(const Vec2f& factor);
        void setVelocity(float vx, float vy);
        void setVelocity(const Vec2f& vel);
        void addForce(float fx, float fy);
        void addForce(const Vec2f& fv);
        void clearForces();
        float getAX() const;
        float getAY() const;
        float getLife() const;
        void setLife(float life);
        void initRandomParticle(float mx, float my);
        void initRandP();
        void integrate(float dt);
        int getRadius() const;
    };
}

#endif // !PARTICLE_HPP