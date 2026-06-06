#ifndef CIRCLE_COLLIDER_HPP
#define CIRCLE_COLLIDER_HPP

#include "collisions/Collider.hpp"
#include "math/Vec.hpp"

namespace collisions
{
    class CircleCollider : public Collider
    {
    public:
        CircleCollider(float x, float y, float radius, float restitution = 0.86f);

        void setPosition(float x, float y);
        void resolve(particles::Particle& particle) override;

    private:
        Vec2f center{};
        float radius{};
        float restitution{};
    };
}

#endif
