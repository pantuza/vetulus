#!/bin/bash

# Script that tests the stack service


echo
echo "#"
echo "# Testing Vetulus Stack service"
echo "#"
echo

mkdir -p ../services/stack/build/
cd ../services/stack/build/

test_bin_file=test_stack_server

MAX_TRIES=10;

MSG_TYPE=0;

for i in $(seq 1 $MAX_TRIES);
do
    if [ -e "$test_bin_file" ]; then

        MSG_TYPE=1;

        netstat -antl | grep 42500 > /dev/null;
        if [ "$?" -eq "0" ]; then
            echo "Service ready!";
            break;
        fi;
    fi;

    if [ "$MSG_TYPE" -eq "0" ]; then
        echo "[$i] Waiting for test binary.."
    elif [ "$MSG_TYPE" -eq "1" ]; then
        echo "[$i] Waiting service to listen.."
    fi;
    sleep 5;
done;

./test_stack_server /vetulus/config/files/stack_client.conf
