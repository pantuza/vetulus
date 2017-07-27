#!/bin/sh

# Installs Pistache library

echo "- Installing Pistache.."

git clone https://github.com/oktal/pistache.git

cd pistache
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make

if [ $(which sudo) ]; then
    sudo make install
else
    make install
fi

if [ "$?" == 0 ]; then
    cd ../..
    rm -rf pistache
    echo "Done";
else
    cd ../..
    echo "Fail";
    exit 1
fi
