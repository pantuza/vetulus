
cmake_minimum_required (VERSION 3.0)


project (vetulus_gate)


# Sets major and minor versions
set (vetulus_gate_VERSION_MAJOR 0)
set (vetulus_gate_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Configuration module files
file(GLOB Config_SRC
    "../config/config.cc"
    "../config/config.h"
)

# Adds include directory
set(Headers_SRC "../include")
include_directories(${Headers_SRC})



# Target binary
add_executable(vetulus_gate gate.cc pool.cc ${Config_SRC} ${Headers_SRC}/spdlog)
# add_executable(test_vetulus_gate test_gate.cc ${Headers_SRC}/json.hpp ${Headers_SRC}/spdlog)

# target_link_libraries(test_vetulus_api gtest)

# Links binary with pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(vetulus_gate Threads::Threads)
# target_link_libraries(test_vetulus_gate Threads::Threads)
