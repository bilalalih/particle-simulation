#include "forces/DragForce.hpp"

namespace forces
{
    DragForce::DragForce(float d) : drag(d)
    {}

    void DragForce::apply(particles::Particle& p)
    {
        p.addForce(-p.getVX() * drag, -p.getVY() * drag);
    }
}