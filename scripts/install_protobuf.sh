#!/bin/bash

# Installs protobuf compiler and shared libraries

echo
echo "#"
echo "# Installing Protobuf.."
echo "#"
echo


git clone https://github.com/google/protobuf.git

cd protobuf

./autogen.sh
./configure
make

if [ $(which sudo) ]; then
    sudo make install
    sudo ldconfig
else
    make install
    ldconfig
fi


if [ "$?" == "0" ]; then
    cd ../
    rm -rf protobuf
    echo "Done";
    exit 0;
else
    cd ../
    echo "Fail";
    exit 1
fi
