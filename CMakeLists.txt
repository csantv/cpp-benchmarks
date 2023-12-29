cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release CACHE STRING "build type")

project(cpp-benchmarks LANGUAGES CXX ASM_NASM)
add_executable(${PROJECT_NAME})

include(FetchContent)
find_package(TBB REQUIRED)
find_package(Threads REQUIRED)

set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_Declare(
    googlebenchmark
    URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.tar.gz
)

FetchContent_MakeAvailable(googlebenchmark)

target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark TBB::tbb Threads::Threads)
