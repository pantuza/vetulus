#!/bin/bash

# Installs gRPC library

echo
echo "#"
echo "# Installing gRPC.."
echo "#"
echo

git clone https://github.com/grpc/grpc.git

cd grpc
git submodule update --init

mkdir build
cd build
cmake ..
make

if [ $(which sudo) ]; then
    sudo make install
else
    make install
fi

if [ "$?" == 0 ]; then
    cd ../..
    rm -rf grpc
    echo "Done";
else
    cd ../..
    echo "Fail";
    exit 1
fi
