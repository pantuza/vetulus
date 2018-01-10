#!/bin/bash

# Script that tests the Proto service


echo
echo "#"
echo "# Testing Vetulus Proto service"
echo "#"
echo

mkdir -pv ../manager/build/
cd ../manager/build/

test_bin_file=test_proto_server

MAX_TRIES=10;

MSG_TYPE=0;

PORT=42501;


for i in $(seq 1 $MAX_TRIES);
do
    if [ -e "$test_bin_file" ]; then

        MSG_TYPE=1;

        netstat -antl | grep $PORT > /dev/null;
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

./test_proto_server /vetulus/config/files/proto_client.conf
