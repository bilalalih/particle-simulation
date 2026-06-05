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

        void update(float dt, ParticleSystem& system);
    private:

        float x {};
        float y {};
        bool active {};
        float emissionRate{ 300 };
        float accumulator;
    };
    
}
#endif