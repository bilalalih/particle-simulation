cmake_minimum_required(VERSION 3.20)

project(
    ParticleSimulator
    LANGUAGES CXX
)

set(
    CMAKE_CXX_STANDARD 20
)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_subdirectory(engine)

add_executable(
    particle_sim
    src/main.cpp
)

target_link_libraries(
    particle_sim
    PRIVATE
    engine
)