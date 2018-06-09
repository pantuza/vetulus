#!/bin/bash

# Script that compile and run the Proto service


echo
echo "#"
echo "# Building Vetulus Proto service"
echo "#"
echo

cd ../manager/
mkdir -pv build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Coverage

make


echo
echo "#"
echo "# Running Vetulus Proto service"
echo "#"
echo
./manager_server /vetulus/config/files/manager_server.conf
