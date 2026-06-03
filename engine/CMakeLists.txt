add_library(engine STATIC
    rendering/Texture.cpp
    core/Utils.cpp
    core/Globals.cpp
    rendering/DrawUtils.cpp
    particles/Particle.cpp
)

target_include_directories(
    engine
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    engine
    PUBLIC
    SDL3::SDL3
    SDL3_image::SDL3_image
)