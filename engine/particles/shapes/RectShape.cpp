#include "particles/shapes/RectShape.hpp"
#include <random>

namespace particles
{
    RectShape::RectShape(float px, float py, float w, float h)
        : x(px), y(py), width(w), height(h)
    {
    }

    void RectShape::setPosition(float px, float py)
    {
        x = px;
        y = py;
    }

    std::pair<float, float> RectShape::sample()
    {
        static thread_local std::mt19937 rng(std::random_device{}());

        std::uniform_real_distribution<float> xDist(-width * 0.5f, width * 0.5f);
        std::uniform_real_distribution<float> yDist(-height * 0.5f, height * 0.5f);
        return {x + xDist(rng), y + yDist(rng)};
    }
}
