#include "particles/shapes/CircleShape.hpp"
#include <cmath>
#include <random>

namespace particles
{
    CircleShape::CircleShape(float px, float py, float r)
    :
    x(px), y(py), radius(r)
    {}

    void CircleShape::setPosition(float px, float py)
    {
        x=px;
        y=py;
    }

    std::pair<float,float> CircleShape::sample()
    {
        static thread_local std::mt19937 rng(std::random_device{}());
        static std::uniform_real_distribution<float> angleDist(0.0f, 6.28318f);

        std::uniform_real_distribution<float> radiusDist(0.0f, radius);
        float angle = angleDist(rng);
        float dist = radiusDist(rng);

        return
        {
            x + cos(angle) * dist,
            y + sin(angle) * dist
        };
    }
}