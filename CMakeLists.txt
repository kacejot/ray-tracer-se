cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

project(ray-tracer)
file (GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/external/glm)
add_executable(${PROJECT_NAME} ${SOURCES})
