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

./test_vetulus_config
