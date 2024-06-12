cmake_minimum_required(VERSION 3.10)

project(ParticleSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE INTERNAL "" FORCE)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED HINTS /opt/homebrew/opt/sfml/lib/cmake/SFML)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(ParticleSimulation ${SOURCES})

target_link_libraries(ParticleSimulation PRIVATE sfml-system sfml-window sfml-graphics)
