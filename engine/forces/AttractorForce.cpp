#include "forces/AttractorForce.hpp"
#include <algorithm>
#include <cmath>

namespace forces
{
    AttractorForce::AttractorForce(float x, float y, float strength_)
        : position{x, y}, strength(strength_)
    {
    }

    void AttractorForce::setPosition(float x, float y)
    {
        position.x() = x;
        position.y() = y;
    }

    void AttractorForce::apply(particles::Particle& particle)
    {
        Vec2f delta{
            position.x() - particle.getX(),
            position.y() - particle.getY()
        };

        float distanceSquared = delta.x() * delta.x() + delta.y() * delta.y();
        distanceSquared = std::max(distanceSquared, minDistanceSquared);

        float distance = std::sqrt(distanceSquared);
        float acceleration = strength / distanceSquared;
        particle.addForce((delta.x() / distance) * acceleration, (delta.y() / distance) * acceleration);
    }
}
