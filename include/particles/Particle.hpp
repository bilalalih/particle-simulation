#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "math/Vec.hpp"

class Particle
{
private:
    Vec2f position;
    Vec2f velocity;
    float radius = 4;
    float life;

public:
    Particle(float x, float y, float vx, float vy);
    Particle(float x, float y, float vx, float vy, float radius);
    float getX() const;
    float getY() const;
    float getLife() const;
    void initRandomParticle(float mx, float my);
    void initRandP();
    void update(const float g, const int h, const float dt);
    int getRadius() const;
};
#endif // !PARTICLE_HPP