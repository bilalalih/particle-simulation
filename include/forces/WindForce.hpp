#ifndef WIND_FORCE_HPP
#define WIND_FORCE_HPP

#include "forces/Force.hpp"

namespace forces
{
    class WindForce : public Force
    {
    public:
        WindForce(float strength);
        void apply(particles::Particle& p, float dt) override;

    private:
        float strength {};
    };
}
#endif