#!/bin/bash

# Installs Google Test library

echo
echo "#"
echo "# Installing Google Test.."
echo "#"
echo

# Forcing directory path
cd /vetulus/scripts/

git clone https://github.com/google/googletest.git

cd googletest

mkdir build
cd build
cmake -D BUILD_GTEST=ON -G Ninja ..
ninja

if [ $(which sudo) ]; then
    sudo ninja install
else
    ninja install
fi

if [ "$?" == 0 ]; then
    echo "Done";
else
    echo "Fail";
    exit 1
fi
