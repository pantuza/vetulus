#!/bin/bash



#
# Compiles only the source code
#
code ()
{
    find $(pwd) -type d -iname build | while read directory;
    do
        cd $directory && make;
    done;
}



#
# Configure using cmake and build source
#
build ()
{
    echo "# Building Configuration library"
    cd /vetulus/config
    mkdir -vp build
    cd build
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Coverage ..
    time ninja -j 4

    echo "Building Vetulus Stack service"
    cd /vetulus/services/stack
    mkdir -pv build
    cd build
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Coverage ..
    time ninja -j 4

    echo "Building Vetulus Manager service"
    cd /vetulus/manager/
    mkdir -pv build
    cd build
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Coverage ..
    time ninja -j 4
}



#
# Execution control of the compile.sh script
#
case "$1" in
    code)
        code
        ;;
    *)
        build
        ;;
esac;
