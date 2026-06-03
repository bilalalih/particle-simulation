#include "particles/Particle.hpp"

Particle::Particle(float x, float y) : position{ x, y }
{
}
int Particle::getX() const { return position.at(0); }
int Particle::getY() const { return position.at(1); }