#ifndef VORTEX_FORCE_HPP
#define VORTEX_FORCE_HPP

#include "forces/Force.hpp"
#include "math/Vec.hpp"

namespace forces
{
    class VortexForce : public Force
    {
    public:
        VortexForce(float x, float y, float swirlStrength, float inwardStrength);

        void setPosition(float x, float y);
        void apply(particles::Particle& particle) override;

    private:
        Vec2f center{};
        float swirlStrength{};
        float inwardStrength{};
        float minDistance{35.0f};
    };
}

#endif
