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
cp watchdog.sh /etc/init.d/
chmod +x /etc/init.d/watchdog.sh
ln -s /etc/init.d/watchdog.sh /etc/rc.d/

echo "Done"