cmake_minimum_required (VERSION 3.0)


project (vetulus_api)


# Sets major and minor versions
set (vetulus_api_VERSION_MAJOR 0)
set (vetulus_api_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Configuration module files
file(GLOB Config_SRC
    "../config/config.cc"
    "../config/config.h"
)


# Target binary
add_executable(vetulus_api api.cc ${Config_SRC})
add_executable(test_vetulus_api test_api.cc)

# Links binary with pistache library
target_link_libraries(vetulus_api pistache)
target_link_libraries(test_vetulus_api gtest)

# Links binary with pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(vetulus_api Threads::Threads)
