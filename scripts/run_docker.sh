#!/bin/bash



#
# Build Config
#
echo "# Building Configuration library"
cd /vetulus/config
mkdir build
cd build
cmake -G Ninja ..
ninja



#
# Stack service
#
echo "Building Vetulus Stack service"
cd /vetulus/services/stack
mkdir -pv build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Coverage

make

echo "Running Vetulus Stack service"
./stack_server /vetulus/config/files/stack_server.conf &



#
# Proto service
#
echo "Building Vetulus Proto service"
cd /vetulus/manager/
mkdir -pv build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Coverage

make

echo "Running Vetulus Proto service"
./manager_server /vetulus/config/files/manager_server.conf
