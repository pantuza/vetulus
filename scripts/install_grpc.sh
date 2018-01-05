#!/bin/bash

# Installs gRPC library

echo
echo "#"
echo "# Installing gRPC.."
echo "#"
echo

git clone -b $(curl -s -L https://grpc.io/release) https://github.com/grpc/grpc.git

cd grpc
git submodule update --init
make

if [ $(which sudo) ]; then
    sudo make install
else
    make install
fi

if [ "$?" == "0" ]; then
    cd ../
    rm -rf grpc
    echo "Done";
    exit 0;
else
    cd ../
    echo "Fail";
    exit 1
fi
