#!/bin/bash

# Installs protobuf compiler and shared libraries

echo
echo "#"
echo "# Installing Protobuf.."
echo "#"
echo

# Forcing directory path
cd /vetulus/scripts/


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
    echo "Done";
else
    echo "Fail";
    exit 1
fi
