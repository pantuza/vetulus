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
    ninja

    echo "Building Vetulus Stack service"
    cd /vetulus/services/stack
    mkdir -pv build
    cd build
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Coverage ..
    ninja

    echo "Building Vetulus Proto service"
    cd /vetulus/manager/
    mkdir -pv build
    cd build
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Coverage ..
    ninja
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
