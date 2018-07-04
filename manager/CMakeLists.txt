# Minimum CMake required
cmake_minimum_required(VERSION 3.0)


# Project
project(VetulusMaster)


# Adds include directory
set(Headers_SRC "../include")
include_directories(${Headers_SRC})


# Configuration module files
file(GLOB Config_SRC
    "../config/config.cc"
    "../config/config.h"
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# Protobuffers files path
set(protobuffers_path "../../protos")


set(service_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/service.pb.cc")
set(service_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/service.pb.h")


# Custom command to build Service messages classes
add_custom_command(
    OUTPUT  "${service_proto_srcs}" "${service_proto_hdrs}"
    COMMAND "protoc"
    ARGS -I "${protobuffers_path}" --cpp_out="${CMAKE_CURRENT_BINARY_DIR}"
         "${protobuffers_path}/service.proto"
)


set(service_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/service.grpc.pb.cc")
set(service_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/service.grpc.pb.h")

# Custom command to build service through gRPC
add_custom_command(
      OUTPUT "${service_grpc_srcs}" "${service_grpc_hdrs}"
      COMMAND "protoc"
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" -I "${protobuffers_path}"
      --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin
        "${protobuffers_path}/service.proto"
)


# Generated include directory
include_directories("${CMAKE_CURRENT_BINARY_DIR}")


# Code coverage
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
endif()


# Abstract Data Types services implementation
set(adt_services "../services/")
include_directories(${adt_services})


# Builds Server binary
add_executable(manager_server
    "manager_server.cc"
    "proto_loader.h"
    ${Config_SRC}
    ${Headers_SRC}/spdlog
    ${service_proto_srcs}
    ${service_grpc_srcs}
    "${adt_services}"
)
target_link_libraries(manager_server protobuf protoc grpc++)

# Build manager test executable
add_executable(test_manager_server
    "test_manager_server.cc"
    ${Config_SRC}
    ${service_proto_srcs}
    ${service_grpc_srcs}
)
target_link_libraries(test_manager_server gtest protobuf grpc++)


# Builds processes test executable
add_executable(test_process
    "test_process.cc"
)
target_link_libraries(test_process gtest)


# Builds dispatcher test executable
add_executable(test_dispatcher
    "test_dispatcher.cc"
)
target_link_libraries(test_dispatcher gtest)


#
# Links binaries with gcov Coverage)
#
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    target_link_libraries(test_manager_server gcov)
    target_link_libraries(test_process gcov)
    target_link_libraries(test_dispatcher gcov)
endif()



# Links binary with pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(manager_server Threads::Threads)
target_link_libraries(test_manager_server Threads::Threads)
target_link_libraries(test_process Threads::Threads)
target_link_libraries(test_dispatcher Threads::Threads)
