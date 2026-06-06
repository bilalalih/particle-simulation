#ifndef EMISSION_SHAPE_HPP
#define EMISSION_SHAPE_HPP

#include <utility>

namespace particles
{
    class EmissionShape
    {
    public:

        virtual ~EmissionShape() = default;
        virtual std::pair<float,float> sample() = 0;
};

}

#endif