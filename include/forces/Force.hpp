#ifndef FORCE_HPP
#define FORCE_HPP

#include "particles/Particle.hpp"

namespace forces
{
    class Force
    {
    public:
        virtual ~Force() = default;
        virtual void apply(particles::Particle& particle, float dt) = 0;
    };
}
#endif