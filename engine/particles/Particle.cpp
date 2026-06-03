#include "particles/Particle.hpp"

Particle::Particle(float x, float y, float vx, float vy) : position{ x, y }, velocity{vx , vy}
{
}
int Particle::getX() const { return position.at(0); }
int Particle::getY() const { return position.at(1); }
int Particle::getRadius() const { return static_cast<int>(radius); }