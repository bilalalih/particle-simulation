#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "math/Vec.hpp"

struct Particle
{
    Vec2f position;
    float radius;

    Particle(float x, float y);

    int getX() const;
    int getY() const;
};
#endif // !PARTICLE_HPP