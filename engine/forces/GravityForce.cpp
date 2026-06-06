#include "forces/GravityForce.hpp"

namespace forces
{
    GravityForce::GravityForce(float g) : gravity(g)
    {}

    void GravityForce::apply(particles::Particle& p, float dt)
    {
        p.addVelocity(0, gravity * dt);
    }
}