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


# Targets stack_(client|server)
foreach(_target stack_server stack_client)

    add_executable(${_target}
        "${_target}.cc"
        ${Config_SRC}
        ${dog_proto_srcs}
        ${stack_proto_srcs}
        ${stack_grpc_srcs}
    )

    target_link_libraries(${_target} protobuf)
    target_link_libraries(${_target} grpc++)
endforeach()
