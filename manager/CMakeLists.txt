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


# Executable for generating c++ code
add_executable(vetulus_master
    proto_loader.cc
    ${Headers_SRC}/spdlog
    ${service_proto_srcs}
    ${service_grpc_srcs}
    ${Config_SRC}
)


target_link_libraries(vetulus_master protobuf protoc grpc++)


# Builds Server binary
add_executable(proto_server
    "proto_server.cc"
    ${Config_SRC}
    ${Headers_SRC}/spdlog
    ${service_proto_srcs}
    ${service_grpc_srcs}
)
target_link_libraries(proto_server protobuf grpc++)


# Build test executable
add_executable(test_proto_server
    "test_proto_server.cc"
    ${Config_SRC}
    ${service_proto_srcs}
    ${service_grpc_srcs}
)
target_link_libraries(test_proto_server gtest protobuf grpc++)


# Links binary with pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(vetulus_master Threads::Threads)
target_link_libraries(proto_server Threads::Threads)
target_link_libraries(test_proto_server Threads::Threads)
