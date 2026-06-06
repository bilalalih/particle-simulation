#include "forces/GravityForce.hpp"

namespace forces
{
    GravityForce::GravityForce(float g) : gravity(g)
    {}

    void GravityForce::apply(particles::Particle& p)
    {
        p.addForce(0, gravity);   
    }
}