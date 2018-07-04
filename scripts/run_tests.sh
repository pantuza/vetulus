#!/bin/bash


#
# Run tests of every module from Vetulus
#




# Waits until services are up and running
SLEEP_TIME=10
MAX_RETRIES=15

for i in $(seq 1 ${MAX_RETRIES});
do
    netstat -antl | grep "4242" | grep -i LISTEN

    # When server is up we break the waiting and try to run tests
    if [ "$?" -eq "0" ]; then
        break;
    fi;

    echo "[${i}] Waiting Vetulus service.."
    sleep ${SLEEP_TIME};
done;


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
