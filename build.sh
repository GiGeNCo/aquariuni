#!/bin/bash
# Simple build script to compile project

# Build Utils
cd ${PWD##}/src
make clean
make

# Check we can run sudo command or not
CAN_I_RUN_SUDO=$(sudo -n uptime 2>&1 | grep "load" | wc -l)
if [ ${CAN_I_RUN_SUDO} -gt 0 ]
then
    echo "Installing..."
else
    echo "You must have a root access"
fi

# Install program
sudo make install

# Install watchdog
cd ..
sudo cp watchdog /etc/init.d/
sudo chmod +x /etc/init.d/watchdog

echo "Done"
