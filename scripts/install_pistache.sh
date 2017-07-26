#!/bin/bash

# Installs Pistache library

echo "- Installing Pistache.."

git clone https://github.com/oktal/pistache.git
git submodule update --init

pushd pistache
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install

if [ "$?" == 0 ]; then
    popd
    rm -rf pistache
    echo "Done";
else
    popd
    echo "Fail";
    exit 1
fi
