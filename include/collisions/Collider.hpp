#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "particles/Particle.hpp"

namespace collisions
{
    class Collider
    {
    public:
        virtual ~Collider() = default;
        virtual void resolve(particles::Particle& particle) = 0;
    };
}

#endif
