#ifndef DRAG_FORCE_HPP
#define DRAG_FORCE_HPP

#include "forces/Force.hpp"

namespace forces
{
    class DragForce : public Force
    {
    public:
        DragForce(float drag);
        void apply(particles::Particle& particle) override;

    private:
        float drag {};
    };
}
#endif