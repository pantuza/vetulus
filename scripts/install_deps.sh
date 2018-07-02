#!/bin/bash

# Shell script to install some project dependencies

echo "PROJECT DEPENDENCIES INSTALLATION"
echo
echo "* You should run this script inside scripts directory"

# Forcing directory path
cd /vetulus/scripts/

# Installs gRPC library
./install_grpc.sh
