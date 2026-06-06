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

    void Particle::initRandomParticle(float mx, float my)
    {
        position.x() = mx; 
        position.y() = my; 
        life = 15.0f;
        velocity.y() = -200 - (rand() % 300); 
        velocity.x() = -(rand() % 400) - 200;
    }

    void Particle::initRandP()
    {
        velocity.x() = (rand() % 800) - 400;
        velocity.y() = -(rand() % 800);
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
        position += velocity * dt; 
        life -= dt;               
    }

    int Particle::getRadius() const 
    { 
        return static_cast<int>(radius); 
    }

}
