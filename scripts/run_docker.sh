#!/bin/bash



cat /vetulus/scripts/welcome-message.txt;


echo "Running Vetulus Stack service"
cd /vetulus/services/stack/build/ && ./stack_server /vetulus/config/files/stack_server.conf &

echo "Running Vetulus Manager service"
cd /vetulus/manager/build/ && ./manager_server /vetulus/config/files/manager_server.conf
