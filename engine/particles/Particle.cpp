#include <random>
#include "particles/Particle.hpp"

namespace particles
{
    Particle::Particle() noexcept
    : position{0.f, 0.f}, velocity{0.f, 0.f}, radius(4), life(0.f)
    {
    }

    Particle::Particle(float x, float y, float vx, float vy) : position{ x, y }, velocity{vx , vy}, radius(4), life(0.f)
    {
    }

    Particle::Particle(float x, float y, float vx, float vy, float radius_) : position{ x, y }, velocity{vx , vy}, radius(radius_)
    {
    }

    float Particle::getX() const 
    { 
        return position.x(); 
    }

    float Particle::getY() const 
    { 
        return position.y(); 
    }

    float Particle::getVX() const
    {
        return velocity.x();
    }

    float Particle::getVY() const
    {
        return velocity.y();
    }

    const Vec2f& Particle::getPosition() const
    {
        return position;
    }

    const Vec2f& Particle::getVelocity() const
    {
        return velocity;
    }

    void Particle::setX(float x)
    {
        position.x() = x;
    }

    void Particle::setY(float y)
    {
        position.y() = y;
    }

    void Particle::setPosition(float x, float y)
    {
        position.x() = x;
        position.y() = y;
    }

    void Particle::setVY(float vy)
    {
        velocity.y() = vy;
    }

    void Particle::setVX(float vx)
    {
        velocity.x() = vx;
    }

    void Particle::addVelocity(float dx, float dy) 
    { 
        velocity.x() += dx; 
        velocity.y() += dy; 
    }

    void Particle::addVelocity(const Vec2f& dv)
    {
        velocity += dv;
    }

    void Particle::mulVelocity(float dx, float dy)
    {
        velocity.x() *= dx; 
        velocity.y() *= dy; 
    }

    void Particle::mulVelocity(const Vec2f& factor)
    {
        velocity.x() *= factor.x();
        velocity.y() *= factor.y();
    }

    void Particle::setVelocity(float dx, float dy)
    {
        velocity.x() = dx; 
        velocity.y() = dy; 
    }

    void Particle::setVelocity(const Vec2f& vel)
    {
        velocity = vel;
    }

    void Particle::addForce(float fx, float fy)
    {
        acceleration.x() += fx;
        acceleration.y() += fy;
    }

    void Particle::addForce(const Vec2f& fv)
    {
        acceleration += fv;
    }

    void Particle::clearForces()
    {
        acceleration.x() = 0;
        acceleration.y() = 0;
    }

    float Particle::getAX() const 
    {
        return acceleration.x();
    }

    static std::mt19937& getParticleRng()
    {
        static thread_local std::mt19937 rng(std::random_device{}());
        return rng;
    }

    float Particle::getAY() const 
    {
        return acceleration.y();
    }

    void Particle::initRandomParticle(float mx, float my)
    {
        static std::uniform_int_distribution<int> velYDist(0, 299);
        static std::uniform_int_distribution<int> velXDist(0, 399);

        position.x() = mx; 
        position.y() = my; 
        life = 15.0f;
        velocity.y() = -200.0f - static_cast<float>(velYDist(getParticleRng()));
        velocity.x() = -static_cast<float>(velXDist(getParticleRng())) - 200.0f;
    }

    void Particle::initRandP()
    {
        static std::uniform_int_distribution<int> range800(0, 799);

        velocity.x() = static_cast<float>(range800(getParticleRng())) - 400.0f;
        velocity.y() = -static_cast<float>(range800(getParticleRng()));
        life = 10;
    }

    float Particle::getLife() const
    {
        return life;
    }

    void Particle::setLife(float l)
    {
        life = l;
    }

    void Particle::integrate(float dt)
    {                   
        velocity += acceleration * dt;
        position += velocity * dt; 
        life -= dt;
        clearForces();               
    }

    int Particle::getRadius() const 
    { 
        return static_cast<int>(radius); 
    }

}
