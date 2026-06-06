#include "collisions/CircleCollider.hpp"
#include <cmath>

namespace collisions
{
    CircleCollider::CircleCollider(float x, float y, float radius_, float restitution_)
        : center{x, y}, radius(radius_), restitution(restitution_)
    {
    }

    void CircleCollider::setPosition(float x, float y)
    {
        center.x() = x;
        center.y() = y;
    }

    void CircleCollider::resolve(particles::Particle& particle)
    {
        Vec2f delta{
            particle.getX() - center.x(),
            particle.getY() - center.y()
        };

        float minDistance = radius + particle.getRadius();
        float distanceSquared = delta.x() * delta.x() + delta.y() * delta.y();
        if (distanceSquared >= minDistance * minDistance)
        {
            return;
        }

        float distance = std::sqrt(distanceSquared);
        Vec2f normal{1.0f, 0.0f};
        if (distance > 0.001f)
        {
            normal = {delta.x() / distance, delta.y() / distance};
        }

        particle.setPosition(
            center.x() + normal.x() * minDistance,
            center.y() + normal.y() * minDistance
        );

        float normalVelocity = particle.getVX() * normal.x() + particle.getVY() * normal.y();
        if (normalVelocity < 0.0f)
        {
            particle.addVelocity(
                -(1.0f + restitution) * normalVelocity * normal.x(),
                -(1.0f + restitution) * normalVelocity * normal.y()
            );
        }
    }
}
