#!/bin/bash

find $(pwd) -type d -iname build | while read directory;
do
    cd $directory && make;
done;
