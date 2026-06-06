#ifndef PARTICLE_EMITTER_HPP
#define PARTICLE_EMITTER_HPP

namespace particles
{
    class ParticleSystem;

    class ParticleEmitter
    {
    public:
        void setPosition(float px, float py);
        
        void start();
        void stop();
        void setRate(float rate);
        void setVelocity(float vx, float vy);
        void setSpread(float degrees);

        void update(float dt, ParticleSystem& system);
    private:

        float x {};
        float y {};

        float vx {};
        float vy {};

        float spread{0};
        bool active {false};

        float emissionRate{ 100 };
        float accumulator;
    };
    
}
#endif