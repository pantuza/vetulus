#!/bin/bash

# Installs gRPC library

echo
echo "#"
echo "# Installing gRPC.."
echo "#"
echo

# Forcing directory path
cd /vetulus/scripts/


git clone -b $(curl -s -L https://grpc.io/release) https://github.com/grpc/grpc.git

cd grpc
git submodule update --init
make -j 4

if [ $(which sudo) ]; then
    sudo make install
else
    make install
fi

ldconfig


#
# This part of the script will be removed when the problem with library
# links were solved.
#
SYS_LIB_PATH=/usr/local/lib/
echo "Creating symbolic links on object libraries"

find ${SYS_LIB_PATH} -iname "libgrpc++*.so" | while read library; do

    # Creates a symbolic link from each library to one with sufix
    ln -svf "${library}" "${library}.1";
done



# Finish installation and remove repository
if [ "$?" == "0" ]; then
    cd /vetulus/scripts
    rm -rf grpc
    echo "Done";
    exit 0;
else
    echo "Fail";
    exit 1
fi
