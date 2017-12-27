#!/bin/bash

# Script that compile and run the Stack service


echo
echo "#"
echo "# Building Vetulus Stack service"
echo "#"
echo

cd ../services/stack
mkdir -pv build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Coverage

make


echo
echo "#"
echo "# Running Vetulus Stack service"
echo "#"
echo
./stack_server /vetulus/config/files/stack_server.conf
