#!/bin/bash

# Shell script to install some project dependencies

echo "PROJECT DEPENDENCIES INSTALLATION"
echo
echo "* You should run this script from inside scripts directory"

# Installs pistache library
./install_pistache.sh

# Installs Google Test library
./install_googletest.sh

# Installs gRPC library
./install_grpc.sh
