/*
 * src/aquariuni.c
 *
 *  Copyleft (C)  2015  IliaUni Robotics TeaM
 *
 * Main source file for aquariuni project.
 */


#include "stdinc.h"
#include "dht11.h"
#include "relay.h"
#include "slog.h"
#include "info.h"
#include "lcd.h"


/*
 * clean_up - Function closes all relay when exit;
 */
void clean_up(int sig) 
{
    close_relay(RELAYPIN1);
    close_relay(RELAYPIN2);
    close_relay(RELAYPIN3);
    close_relay(RELAYPIN4);
    close_relay(RELAYPIN5);

    slog(0, SLOG_LIVE, "Cleaning up..");
    exit(0);
}


/* Main function */
int main(void)
{
    /* Used variables */
    DHTSensorValues dht;
    SystemDate date;
    char tempstr[128];
    char humstr[128];
    int status, idp = 0, lon = 0;

    /* Greet users */
    greet("AquariUni");

    /* Initialize logger */
    init_slog("aquariuni", "config.cfg", 3);

    /* Set up writing pin */
    status = wiringPiSetup();
    if(status == -1) exit(1);

    /* Interrupt and termination (ANSI) */
    signal(SIGINT, clean_up);
    signal(SIGTERM, clean_up);
    signal(SIGILL, clean_up);
    signal(SIGSEGV, clean_up);

    /* Initialize modules */
    bzero(tempstr, sizeof(tempstr));
    bzero(humstr, sizeof(humstr));
    init_dht_val(&dht);
    init_lcd(); sleep(1);

    /* Initialize relays */
    init_relay(RELAYPIN1, RELAYPIN2, RELAYPIN3, RELAYPIN4, RELAYPIN5 ,0,0,0);

    /* Main loop (never ends) */
    while(1)
    {
        /* Initialize system date */
        get_system_date(&date);

        /* Read data from Humidity/Temperature sensor */
        status = dht11_read_val(&dht);
        if (status) 
        {
            /* Log in terminal */
            slog(0, SLOG_DEBUG, "Humidity: %d %% Temperature: %d *C", dht.humidity, dht.celsius);

            /* Write data on display */
            sprintf(tempstr, "Temperature: %d", dht.celsius);
            lcd_position (0, 0); lcd_puts(tempstr);
            delay(5);
            sprintf(humstr, "Humidity: %d %%", dht.humidity);
            lcd_position (0, 1); lcd_puts(humstr);
            delay(5);
            idp = 1;
        }
        else 
        {
            slog(0, SLOG_ERROR, "Invalid data from Humidity/Temperature sensor");
            if (!idp) 
            {
                lcd_position(0, 0);
                lcd_puts("Ivalid data");
                delay(5);
            }
        }

        /* Open lux relay */
        if (date.hour > 20) open_relay(RELAYPIN1);
        else close_relay(RELAYPIN1);

        /* Open warm relay */
        if (dht.celsius < 15) 
        {
            open_relay(RELAYPIN2);
            open_relay(RELAYPIN3);
            lon = 1;
        }
        else 
        {
            close_relay(RELAYPIN2);
            close_relay(RELAYPIN3);
            lon = 0;
        }

        /* Open humidity relay */
        if (dht.humidity > 45) open_relay(RELAYPIN5);
        else close_relay(RELAYPIN5);

        /* Open cooling relay */
        if (dht.celsius > 25) 
        {
            open_relay(RELAYPIN4);
            open_relay(RELAYPIN3);
        }
        else
        {
            if (!lon) close_relay(RELAYPIN3);
            close_relay(RELAYPIN4);
        }

        delay(3000);
    }

    return 0;
}
