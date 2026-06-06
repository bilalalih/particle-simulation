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
        return position.at(0); 
    }

    float Particle::getY() const 
    { 
        return position.at(1); 
    }

    void Particle::addVelocity(float dx, float dy) 
    { 
        velocity.at(0) += dx; 
        velocity.at(1) += dy; 
    }

    void Particle::mulVelocity(float dx, float dy)
    {
        velocity.at(0) *= dx; 
        velocity.at(1) *= dy; 
    }

    void Particle::setVelocity(float dx, float dy)
    {
        velocity.at(0) = dx; 
        velocity.at(1) = dy; 
    }

    void Particle::initRandomParticle(float mx, float my)
    {
        position.at(0) = mx; 
        position.at(1) = my; 
        life = 15.0f;
        velocity.at(1) = -200 - (rand() % 300); 
        velocity.at(0) = -(rand()%400) - 200;
    }

    void Particle::initRandP()
    {
        velocity.at(0) = (rand()%800)-400;
        velocity.at(1) = -(rand()%800);
        life=10;
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
        position.at(0) += velocity.at(0) * dt; 
        position.at(1) += velocity.at(1) * dt ;
        
        // energy loss
        velocity.at(0) *= 0.995f;
        velocity.at(1) *= 0.999f;
        life -= dt;               
    }

    void Particle::floor(float f)
    {
        if (position.at(1) > f)
        {
            position.at(1) = f;
            velocity.at(1)*=-0.8f;
        }
    }

    int Particle::getRadius() const 
    { 
        return static_cast<int>(radius); 
    }

}
