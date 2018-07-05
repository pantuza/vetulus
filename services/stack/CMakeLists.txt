# Minimum CMake required
cmake_minimum_required(VERSION 3.0)

# Project
project(StackServer)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# Configuration module files
file(GLOB Config_SRC
    "../../config/config.cc"
    "../../config/config.h"
)

# Adds include directory
set(Headers_SRC "../../include")
include_directories(${Headers_SRC})


# Protobuffers files path
set(protobuffers_path "../../../protos")


set(dog_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/dog.pb.cc")
set(dog_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/dog.pb.h")

# Custom command to build Dog sources
add_custom_command(
    OUTPUT  "${dog_proto_srcs}" "${dog_proto_hdrs}"
    COMMAND "protoc"
    ARGS -I "${protobuffers_path}" --cpp_out="${CMAKE_CURRENT_BINARY_DIR}"
         "${protobuffers_path}/dog.proto"
)


set(stack_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/stack.pb.cc")
set(stack_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/stack.pb.h")

# Custom command to build Stack sources
add_custom_command(
    OUTPUT  "${stack_proto_srcs}" "${stack_proto_hdrs}"
    COMMAND "protoc"
    ARGS -I "${protobuffers_path}" --cpp_out="${CMAKE_CURRENT_BINARY_DIR}"
         "${protobuffers_path}/stack.proto"
)


set(stack_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/stack.grpc.pb.cc")
set(stack_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/stack.grpc.pb.h")

# Custom command to build Stack service through gRPC
add_custom_command(
      OUTPUT "${stack_grpc_srcs}" "${stack_grpc_hdrs}"
      COMMAND "protoc"
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" -I "${protobuffers_path}"
      --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin
        "${protobuffers_path}/stack.proto"
)


# Generated include directory
include_directories("${CMAKE_CURRENT_BINARY_DIR}")


# Builds Server binary
add_executable(stack_server
    "stack_server.cc"
    ${Config_SRC}
    ${Headers_SRC}/spdlog
    ${dog_proto_srcs}
    ${stack_proto_srcs}
    ${stack_grpc_srcs}
)
target_link_libraries(stack_server protobuf grpc++ vetulus)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
endif()

add_executable(test_stack_server
    "test_stack_server.cc"
    ${Config_SRC}
    ${dog_proto_srcs}
    ${stack_proto_srcs}
    ${stack_grpc_srcs}
)

target_link_libraries(test_stack_server gtest protobuf grpc++ vetulus)
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    target_link_libraries(test_stack_server gcov)
endif()


# Links binary with pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(test_stack_server Threads::Threads)
