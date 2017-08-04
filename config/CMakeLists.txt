cmake_minimum_required (VERSION 3.0)


project (vetulus_config)


# Sets major and minor versions
set (vetulus_api_VERSION_MAJOR 0)
set (vetulus_api_VERSION_MINOR 1)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Target binary
add_executable(test_vetulus_config config.cc test_config.cc)

# Links binary with Google Test library
target_link_libraries(test_vetulus_config gtest)

# Links binary with pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(test_vetulus_config Threads::Threads)
