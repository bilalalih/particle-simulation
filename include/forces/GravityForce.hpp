#ifndef GRAVITY_FORCE_HPP
#define GRAVITY_FORCE_HPP

#include "forces/Force.hpp"

namespace forces
{
    class GravityForce : public Force
    {
    public:
        GravityForce(float g);
        void apply(particles::Particle& particle, float dt) override;
    
    private:
        float gravity {};
    };
}
#endif