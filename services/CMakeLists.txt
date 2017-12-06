# Minimum CMake required
cmake_minimum_required(VERSION 3.0)

# Project
project(StackServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Protobuf
find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

if(Protobuf_FOUND)
  # Protobuf_FOUND is set for package type "CONFIG"
  set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
  set(_PROTOBUF_PROTOC protobuf::protoc)
elseif(PROTOBUF_FOUND)
  # PROTOBUF_FOUND is set for package type "MODULE"
  set(_PROTOBUF_LIBPROTOBUF ${PROTOBUF_LIBRARIES})
  set(_PROTOBUF_PROTOC ${PROTOBUF_PROTOC_EXECUTABLE})
  include_directories(${PROTOBUF_INCLUDE_DIRS})
else()
  message(WARNING "Failed to locate libprotobuf and protoc!")
endif()

# gRPC
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

# gRPC C++ plugin
get_target_property(gRPC_CPP_PLUGIN_EXECUTABLE gRPC::grpc_cpp_plugin
    IMPORTED_LOCATION_RELEASE)

# Proto file
get_filename_component(stack_proto "stack.proto" ABSOLUTE)
get_filename_component(stack_proto_path "${stack_proto}" PATH)

# Generated sources
protobuf_generate_cpp(stack_proto_srcs stack_proto_hdrs "${stack_proto}")
set(stack_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/stack.grpc.pb.cc")
set(stack_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/stack.grpc.pb.h")
add_custom_command(
      OUTPUT "${stack_grpc_srcs}" "${stack_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" -I "${stack_proto_path}"
        --plugin=protoc-gen-grpc="${gRPC_CPP_PLUGIN_EXECUTABLE}"
        "${stack_proto}"
      DEPENDS "${stack_proto}")

# Generated include directory
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Targets stack_(client|server)
foreach(_target
  stack_client stack_server)
  add_executable(${_target} "${_target}.cc"
    ${stack_proto_srcs}
    ${stack_grpc_srcs})
  target_link_libraries(${_target}
    ${_PROTOBUF_LIBPROTOBUF}
    gRPC::grpc++_unsecure)
endforeach()
