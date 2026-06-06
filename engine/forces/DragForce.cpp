#include "forces/DragForce.hpp"

namespace forces
{
    DragForce::DragForce(float dampingCoefficient) : drag(dampingCoefficient)
    {}

    void DragForce::apply(particles::Particle& p)
    {
        p.addForce(-p.getVX() * drag, -p.getVY() * drag);
    }
}
