add_library(engine STATIC
    rendering/LTexture.cpp
    core/Utils.cpp
    core/Globals.cpp
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