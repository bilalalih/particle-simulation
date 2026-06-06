#include "core/App.hpp"
#include "core/Config.hpp"
#include "collisions/CircleCollider.hpp"
#include "forces/AttractorForce.hpp"
#include "forces/DragForce.hpp"
#include "forces/GravityForce.hpp"
#include "forces/VortexForce.hpp"
#include "forces/WindForce.hpp"
#include "particles/Particle.hpp"
#include "particles/ParticleEmitter.hpp"
#include "particles/ParticleSystem.hpp"
#include "particles/shapes/PointShape.hpp"
#include "particles/shapes/RectShape.hpp"
#include "rendering/ParticleRenderer.hpp"
#include <SDL3/SDL_main.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>

namespace
{
    enum class Experiment
    {
        FireFountain,
        RainCurtain,
        OrbitForge,
        VortexBloom,
        ColliderLab
    };

    struct ExperimentState
    {
        Experiment current{Experiment::FireFountain};
        rendering::ParticleRenderer::Palette palette{rendering::ParticleRenderer::Palette::Fire};
        core::Color background{15, 14, 18, 255};
        float lifeScale{4.0f};
        float mouseX{0.0f};
        float mouseY{0.0f};
        float orbitAccumulator{0.0f};
        forces::AttractorForce* attractor{nullptr};
        forces::VortexForce* vortex{nullptr};
        collisions::CircleCollider* circleCollider{nullptr};
        bool floorEnabled{true};
        bool showObstacle{false};
        float obstacleX{0.0f};
        float obstacleY{0.0f};
        float obstacleRadius{0.0f};
    };

    const char* experimentName(Experiment experiment)
    {
        switch (experiment)
        {
            case Experiment::FireFountain:
                return "1 Fire Fountain";
            case Experiment::RainCurtain:
                return "2 Rain Curtain";
            case Experiment::OrbitForge:
                return "3 Orbit Forge";
            case Experiment::VortexBloom:
                return "4 Vortex Bloom";
            case Experiment::ColliderLab:
                return "5 Collider Lab";
            default:
                return "Particle Experiments";
        }
    }

    void setWindowTitle(core::App& app, Experiment experiment)
    {
        std::string title = "Particle Experiments - ";
        title += experimentName(experiment);
        title += " | 1-5 switch, Space reset, mouse interacts";
        SDL_SetWindowTitle(app.getWindow(), title.c_str());
        SDL_Log("%s", title.c_str());
    }

    void configureExperiment(
        Experiment experiment,
        core::App& app,
        particles::ParticleSystem& particleSystem,
        particles::ParticleEmitter& emitter,
        ExperimentState& state
    )
    {
        particleSystem.clear();
        particleSystem.clearForces();
        particleSystem.clearColliders();
        state.current = experiment;
        state.attractor = nullptr;
        state.vortex = nullptr;
        state.circleCollider = nullptr;
        state.floorEnabled = true;
        state.showObstacle = false;
        state.orbitAccumulator = 0.0f;

        int width = app.getScreenWidth();
        int height = app.getScreenHeight();

        switch (experiment)
        {
            case Experiment::FireFountain:
                state.background = {15, 14, 18, 255};
                state.palette = rendering::ParticleRenderer::Palette::Fire;
                state.lifeScale = 4.0f;
                particleSystem.setMaxParticles(12000);
                particleSystem.addForce(std::make_unique<forces::GravityForce>(650.0f));
                particleSystem.addForce(std::make_unique<forces::DragForce>(0.05f));

                emitter = particles::ParticleEmitter();
                emitter.setShape(std::make_unique<particles::PointShape>(width * 0.5f, height - 45.0f));
                emitter.setPosition(width * 0.5f, height - 45.0f);
                emitter.setRate(900.0f);
                emitter.setVelocity(0.0f, -720.0f);
                emitter.setSpread(38.0f);
                emitter.setParticleLife(4.0f);
                emitter.setParticleRadius(4.0f);
                emitter.start();
                break;

            case Experiment::RainCurtain:
                state.background = {5, 16, 26, 255};
                state.palette = rendering::ParticleRenderer::Palette::Rain;
                state.lifeScale = 2.7f;
                particleSystem.setMaxParticles(16000);
                particleSystem.addForce(std::make_unique<forces::GravityForce>(460.0f));
                particleSystem.addForce(std::make_unique<forces::WindForce>(-55.0f));

                emitter = particles::ParticleEmitter();
                emitter.setShape(std::make_unique<particles::RectShape>(width * 0.5f, -30.0f, width + 300.0f, 30.0f));
                emitter.setRate(1400.0f);
                emitter.setVelocity(45.0f, 620.0f);
                emitter.setSpread(5.0f);
                emitter.setParticleLife(2.7f);
                emitter.setParticleRadius(2.0f);
                emitter.start();
                break;

            case Experiment::OrbitForge:
            {
                state.background = {8, 7, 16, 255};
                state.palette = rendering::ParticleRenderer::Palette::Plasma;
                state.lifeScale = 9.0f;
                state.floorEnabled = false;
                particleSystem.setMaxParticles(18000);

                auto attractor = std::make_unique<forces::AttractorForce>(
                    state.mouseX,
                    state.mouseY,
                    12000000.0f
                );
                state.attractor = attractor.get();
                particleSystem.addForce(std::move(attractor));
                particleSystem.addForce(std::make_unique<forces::DragForce>(0.015f));

                emitter = particles::ParticleEmitter();
                emitter.stop();
                break;
            }

            case Experiment::VortexBloom:
            {
                state.background = {6, 10, 16, 255};
                state.palette = rendering::ParticleRenderer::Palette::Plasma;
                state.lifeScale = 6.0f;
                state.floorEnabled = false;
                particleSystem.setMaxParticles(22000);

                auto vortex = std::make_unique<forces::VortexForce>(
                    state.mouseX,
                    state.mouseY,
                    420000.0f,
                    70000.0f
                );
                state.vortex = vortex.get();
                particleSystem.addForce(std::move(vortex));
                particleSystem.addForce(std::make_unique<forces::DragForce>(0.035f));

                emitter = particles::ParticleEmitter();
                emitter.setShape(std::make_unique<particles::PointShape>(state.mouseX, state.mouseY));
                emitter.setPosition(state.mouseX, state.mouseY);
                emitter.setRate(1100.0f);
                emitter.setVelocity(460.0f, 0.0f);
                emitter.setSpread(360.0f);
                emitter.setParticleLife(6.0f);
                emitter.setParticleRadius(3.0f);
                emitter.start();
                break;
            }

            case Experiment::ColliderLab:
            {
                state.background = {12, 13, 15, 255};
                state.palette = rendering::ParticleRenderer::Palette::Fire;
                state.lifeScale = 5.0f;
                particleSystem.setMaxParticles(15000);
                particleSystem.addForce(std::make_unique<forces::GravityForce>(780.0f));
                particleSystem.addForce(std::make_unique<forces::DragForce>(0.025f));

                state.obstacleX = width * 0.5f;
                state.obstacleY = height * 0.55f;
                state.obstacleRadius = 86.0f;
                state.showObstacle = true;

                auto collider = std::make_unique<collisions::CircleCollider>(
                    state.obstacleX,
                    state.obstacleY,
                    state.obstacleRadius,
                    0.92f
                );
                state.circleCollider = collider.get();
                particleSystem.addCollider(std::move(collider));

                emitter = particles::ParticleEmitter();
                emitter.setShape(std::make_unique<particles::RectShape>(width * 0.5f, 42.0f, width * 0.65f, 16.0f));
                emitter.setRate(1000.0f);
                emitter.setVelocity(0.0f, 230.0f);
                emitter.setSpread(52.0f);
                emitter.setParticleLife(5.0f);
                emitter.setParticleRadius(4.0f);
                emitter.start();
                break;
            }
        }

        setWindowTitle(app, experiment);
    }

    float randomRange(std::mt19937& rng, float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }

    void spawnOrbitParticles(
        particles::ParticleSystem& particleSystem,
        ExperimentState& state,
        float dt,
        int width,
        int height
    )
    {
        static thread_local std::mt19937 rng(std::random_device{}());

        state.orbitAccumulator += 720.0f * dt;
        while (state.orbitAccumulator >= 1.0f)
        {
            float angle = randomRange(rng, 0.0f, 6.2831853f);
            float radius = randomRange(rng, 120.0f, 340.0f);
            float centerX = std::clamp(state.mouseX, 160.0f, static_cast<float>(width) - 160.0f);
            float centerY = std::clamp(state.mouseY, 160.0f, static_cast<float>(height) - 160.0f);

            float x = centerX + std::cos(angle) * radius;
            float y = centerY + std::sin(angle) * radius;
            float tangentX = -std::sin(angle);
            float tangentY = std::cos(angle);
            float speed = std::sqrt(12000000.0f / radius) * randomRange(rng, 0.82f, 1.18f);

            particles::Particle particle(x, y, tangentX * speed, tangentY * speed, 3.0f);
            particle.setLife(randomRange(rng, 5.5f, 9.0f));
            particleSystem.addParticle(particle);

            state.orbitAccumulator -= 1.0f;
        }
    }

    void drawCircle(SDL_Renderer* renderer, float cx, float cy, float radius, core::Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        int ir = static_cast<int>(radius);
        for (int y = -ir; y <= ir; ++y)
        {
            for (int x = -ir; x <= ir; ++x)
            {
                int distanceSquared = x * x + y * y;
                if (distanceSquared <= ir * ir && distanceSquared >= (ir - 3) * (ir - 3))
                {
                    SDL_RenderPoint(renderer, cx + x, cy + y);
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    int frameLimit{-1};
    Experiment startExperiment{Experiment::FireFountain};
    for (int i = 1; i + 1 < argc; ++i)
    {
        if (std::string(argv[i]) == "--frames")
        {
            frameLimit = std::atoi(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "--experiment")
        {
            std::string experimentName = argv[i + 1];
            if (experimentName == "rain")
            {
                startExperiment = Experiment::RainCurtain;
            }
            else if (experimentName == "orbit")
            {
                startExperiment = Experiment::OrbitForge;
            }
            else if (experimentName == "vortex")
            {
                startExperiment = Experiment::VortexBloom;
            }
            else if (experimentName == "collider")
            {
                startExperiment = Experiment::ColliderLab;
            }
            else
            {
                startExperiment = Experiment::FireFountain;
            }
        }
    }

    int exitCode{0};
    core::WindowAndRenderer wdrd;
    core::ScreenCfg cfg;
    core::App application(wdrd, cfg);

    if (!application.init())
    {
        SDL_Log("Unable to initialize program");
        return 1;
    }

    bool quit{false};
    SDL_Event event;
    SDL_zero(event);

    particles::ParticleSystem particleSystem;
    particles::ParticleEmitter emitter;

    rendering::ParticleRenderer particleRenderer;
    if (!particleRenderer.init(application.getRenderer(), 8))
    {
        SDL_Log("Particle renderer initialization failed");
        application.close();
        return 1;
    }

    ExperimentState experimentState;
    experimentState.mouseX = application.getScreenWidth() * 0.5f;
    experimentState.mouseY = application.getScreenHeight() * 0.5f;
    configureExperiment(startExperiment, application, particleSystem, emitter, experimentState);

    Uint64 previous = SDL_GetTicks();
    int width = application.getScreenWidth();
    int height = application.getScreenHeight();
    int frameCount = 0;

    while (!quit)
    {
        Uint64 current = SDL_GetTicks();
        float dt = (current - previous) / 1000.0f;
        dt = std::min(dt, 0.033f);
        previous = current;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_1)
                    {
                        configureExperiment(Experiment::FireFountain, application, particleSystem, emitter, experimentState);
                    }
                    else if (event.key.key == SDLK_2)
                    {
                        configureExperiment(Experiment::RainCurtain, application, particleSystem, emitter, experimentState);
                    }
                    else if (event.key.key == SDLK_3)
                    {
                        configureExperiment(Experiment::OrbitForge, application, particleSystem, emitter, experimentState);
                    }
                    else if (event.key.key == SDLK_4)
                    {
                        configureExperiment(Experiment::VortexBloom, application, particleSystem, emitter, experimentState);
                    }
                    else if (event.key.key == SDLK_5)
                    {
                        configureExperiment(Experiment::ColliderLab, application, particleSystem, emitter, experimentState);
                    }
                    else if (event.key.key == SDLK_SPACE)
                    {
                        configureExperiment(experimentState.current, application, particleSystem, emitter, experimentState);
                    }
                    break;

                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                case SDL_EVENT_MOUSE_MOTION:
                    experimentState.mouseX = event.type == SDL_EVENT_MOUSE_MOTION ? event.motion.x : event.button.x;
                    experimentState.mouseY = event.type == SDL_EVENT_MOUSE_MOTION ? event.motion.y : event.button.y;
                    if (experimentState.current == Experiment::FireFountain)
                    {
                        emitter.setPosition(experimentState.mouseX, experimentState.mouseY);
                    }
                    if (experimentState.attractor)
                    {
                        experimentState.attractor->setPosition(experimentState.mouseX, experimentState.mouseY);
                    }
                    if (experimentState.vortex)
                    {
                        experimentState.vortex->setPosition(experimentState.mouseX, experimentState.mouseY);
                        emitter.setPosition(experimentState.mouseX, experimentState.mouseY);
                    }
                    if (experimentState.circleCollider)
                    {
                        experimentState.obstacleX = experimentState.mouseX;
                        experimentState.obstacleY = experimentState.mouseY;
                        experimentState.circleCollider->setPosition(experimentState.obstacleX, experimentState.obstacleY);
                    }
                    break;

                case SDL_EVENT_QUIT:
                    quit = true;
                    break;

                default:
                    break;
            }
        }

        if (experimentState.current == Experiment::OrbitForge)
        {
            spawnOrbitParticles(particleSystem, experimentState, dt, width, height);
        }
        else
        {
            emitter.update(dt, particleSystem);
        }

        if (experimentState.floorEnabled)
        {
            particleSystem.update(height, dt);
        }
        else
        {
            particleSystem.update(dt);
        }

        application.beginFrame(experimentState.background);
        if (experimentState.showObstacle)
        {
            drawCircle(
                application.getRenderer(),
                experimentState.obstacleX,
                experimentState.obstacleY,
                experimentState.obstacleRadius,
                {90, 230, 210, 190}
            );
        }
        particleRenderer.drawAll(
            particleSystem.getParticles(),
            experimentState.palette,
            experimentState.lifeScale
        );
        application.endFrame();

        ++frameCount;
        if (frameLimit > 0 && frameCount >= frameLimit)
        {
            quit = true;
        }
    }

    particleRenderer.destroy();
    application.close();
    return exitCode;
}
