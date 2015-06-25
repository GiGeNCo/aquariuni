/*
 * aquariuni/main.c
 *
 *  Copyleft (C)  2015  IliaUni Robotics TeaM
 *
 * Main source file for aquariuni project.
 */


#include "stdinc.h"
#include "dht11.h"


/* Main function */
int main(void)
{
    /* Used variables */
    DHTSensorValues dht;
    int status;

    /* Initialize dht sensor values */
    init_dht_val(&dht);
    
    /* Set up writing pin */
    status = wiringPiSetup();
    if(status == -1) exit(1);

    /* Main loop (never ends) */
    while(1)
    {
        /* Read data from Humidity/Temperature sensor */
        status = dht11_read_val(&dht);
        if (status) 
            printf("Humidity: %d %% Temperature: %d *C\n", dht.humidity, dht.celsius);
        else
            printf("Invalid data from Humidity/Temperature sensor..\n");

        delay(3000);
    }

    return 0;
}
