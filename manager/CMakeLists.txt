# Minimum CMake required

cmake_minimum_required(VERSION 3.0)

# Project
project(VetulusMaster)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(vetulus_master proto_loader.cc)

target_link_libraries(vetulus_master protobuf protoc)

# Links binary with pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(vetulus_master Threads::Threads)

