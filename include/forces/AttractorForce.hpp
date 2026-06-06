#ifndef ATTRACTOR_FORCE_HPP
#define ATTRACTOR_FORCE_HPP

#include "forces/Force.hpp"
#include "math/Vec.hpp"

namespace forces
{
    class AttractorForce : public Force
    {
    public:
        AttractorForce(float x, float y, float strength);

        void setPosition(float x, float y);
        void apply(particles::Particle& particle) override;

    private:
        Vec2f position{};
        float strength{};
        float minDistanceSquared{2500.0f};
    };
}

#endif
