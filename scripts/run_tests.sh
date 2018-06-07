#!/bin/bash


#
# Run tests of every module from Vetulus
#



echo "Testing configuration classes"
cd /vetulus/config/build
./test_vetulus_config



echo "Testing Vetulus Stack service"
cd /vetulus/services/stack/build/
./test_stack_server /vetulus/config/files/stack_client.conf



echo "Testing Vetulus Proto service"
cd /vetulus/manager/build/
./test_proto_server /vetulus/config/files/proto_client.conf
