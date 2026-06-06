#include "forces/WindForce.hpp"

namespace forces
{
    WindForce::WindForce(float s) : strength(s)
    {}

    void WindForce::apply(particles::Particle& p, float dt)
    {
        p.addVelocity(strength * dt, 0);
    }
}