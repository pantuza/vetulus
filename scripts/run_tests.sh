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



echo "Testing Vetulus Manager service"
cd /vetulus/manager/build/
./test_manager_server /vetulus/config/files/manager_client.conf



echo "Testing Vetulus Processes namespace"
cd /vetulus/manager/build/
./test_process



echo "Testing Vetulus Dispatcher namespace"
cd /vetulus/manager/build/
./test_dispatcher
