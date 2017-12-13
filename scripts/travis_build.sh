#!/bin/bash

# Build project on Travis CI

echo
echo "#"
echo "# Building Vetulus server"
echo "#"
echo

cd ../config
mkdir build
cd build
cmake -G Ninja ..
ninja

echo
echo "#"
echo "# Testing configuration classes"
echo "#"
echo
./test_vetulus_config
