#!/bin/bash
# Simple watchdog scrip to check process is alove or dead

while [ 1 ]
    do
    if [ "$(pidof aquariuni)" ] 
    then
        sleep 30
    else
        sudo aquariuni &> /dev/null &
        sleep 30
    fi
done
