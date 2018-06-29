#!/bin/bash

# Shell script to install some project dependencies

echo "PROJECT DEPENDENCIES INSTALLATION"
echo
echo "* You should run this script inside scripts directory"

# Installs Google Test library
./install_googletest.sh

# Installs gRPC library
./install_grpc.sh

# Installs protobuf compiler and shared libraries
./install_protobuf.sh
