#!/bin/bash
# Simple watchdog scrip to check process is alove or dead

sleep_time = 30

while [ 1 ]
    do
    if [ "$(pidof aquariuni)" ] 
    then
        sleep $sleep_time
    else
        aquariuni &> /dev/null &
    fi
done