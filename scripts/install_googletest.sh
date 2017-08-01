#!/bin/bash

# Installs Google Test library

echo
echo "#"
echo "# Installing Google Test.."
echo "#"
echo

git clone https://github.com/google/googletest.git

cd googletest

mkdir build
cd build
cmake -G Ninja ..
ninja

if [ $(which sudo) ]; then
    sudo ninja install
else
    ninja install
fi

if [ "$?" == 0 ]; then
    cd ../..
    rm -rf googletest
    echo "Done";
else
    cd ../..
    echo "Fail";
    exit 1
fi
