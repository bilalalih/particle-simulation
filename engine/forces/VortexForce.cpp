#include "forces/VortexForce.hpp"
#include <algorithm>
#include <cmath>

namespace forces
{
    VortexForce::VortexForce(float x, float y, float swirlStrength_, float inwardStrength_)
        : center{x, y}, swirlStrength(swirlStrength_), inwardStrength(inwardStrength_)
    {
    }

    void VortexForce::setPosition(float x, float y)
    {
        center.x() = x;
        center.y() = y;
    }

    void VortexForce::apply(particles::Particle& particle)
    {
        Vec2f delta{
            center.x() - particle.getX(),
            center.y() - particle.getY()
        };

        float distance = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());
        distance = std::max(distance, minDistance);

        Vec2f inward{delta.x() / distance, delta.y() / distance};
        Vec2f tangent{-inward.y(), inward.x()};
        float falloff = 1.0f / distance;

        particle.addForce(
            tangent.x() * swirlStrength * falloff + inward.x() * inwardStrength * falloff,
            tangent.y() * swirlStrength * falloff + inward.y() * inwardStrength * falloff
        );
    }
}
