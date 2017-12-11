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
cd cmake
mkdir build
cd build
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DgRPC_PROTOBUF_PROVIDER=package \
      -DgRPC_ZLIB_PROVIDER=package \
      -DgRPC_CARES_PROVIDER=package \
      -DgRPC_SSL_PROVIDER=package \
      -DCMAKE_BUILD_TYPE=Release \
      ../..

if [ $(which sudo) ]; then
    sudo make -j4 install
else
    make -j4 install
fi

if [ "$?" == 0 ]; then
    cd ../../../
    rm -rf grpc
    echo "Done";
else
    cd ../../../
    echo "Fail";
    exit 1
fi
