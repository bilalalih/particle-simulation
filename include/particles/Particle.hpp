#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "math/Vec.hpp"

struct Particle
{
    Vec2f position;
    Vec2f velocity;
    float radius = 100;

    Particle(float x, float y, float vx, float vy);

    int getX() const;
    int getY() const;
    int getRadius() const;
};
#endif // !PARTICLE_HPP