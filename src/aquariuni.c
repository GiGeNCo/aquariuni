/*
 * src/aquariuni.c
 *
 *  Copyleft (C)  2015  IliaUni Robotics TeaM
 *
 * Main source file for aquariuni project.
 */


#include "stdinc.h"
#include "dbwork.h"
#include "dht11.h"
#include "relay.h"
#include "slog.h"
#include "info.h"
#include "lcd.h"


/* Define relays */
#define LEDS RELAYPIN1
#define LIGHT RELAYPIN2
#define COOLER RELAYPIN3
#define AIRCOOLER RELAYPIN4
#define WARTER RELAYPIN5


/*
 * clean_up - Function closes all relay when exit;
 */
void clean_up(int sig) 
{
    /* Close relays */
    close_relay(LEDS);
    close_relay(LIGHT);
    close_relay(COOLER);
    close_relay(AIRCOOLER);
    close_relay(WARTER);

    /* Clear lcd */
    clear_lcd();

    slog(0, SLOG_LIVE, "Cleaning up..");
    exit(0);
}


/* Main function */
int main(void)
{
    /* Used variables */
    UserInputConfig uic;
    DHTSensorValues dht;
    SystemDate date;
    char tempstr[128];
    char humstr[128];
    int status, invalid_data = 0, light_on = 0;

    /* Greet users */
    greet("AquariUni");

    /* Initialize logger */
    init_slog("aquariuni", "config.cfg", 3);

    /* Set up writing pin */
    status = wiringPiSetup();
    if(status == -1) 
    {
        slog(0, SLOG_FATAL, "Can not setup wiring pi interface");
        exit(1);
    }

    /* Interrupt and termination (ANSI) */
    signal(SIGINT, clean_up);
    signal(SIGTERM, clean_up);
    signal(SIGILL, clean_up);
    signal(SIGSEGV, clean_up);

    /* Initialize modules */
    bzero(tempstr, sizeof(tempstr));
    bzero(humstr, sizeof(humstr));
    ini_uic(&uic);
    init_dht_val(&dht);
    init_lcd(); sleep(1);

    /* Initialize relays */
    init_relay(RELAYPIN1, RELAYPIN2, RELAYPIN3, RELAYPIN4, RELAYPIN5, 0,0,0);

    /* Parse config file */
    status = parse_user_config("config.cfg", &uic);
    if (!status) slog(0, SLOG_WARN, "Can not parse config file");

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
            slog(0, SLOG_DEBUG, "Temperature: %d.%d *C Humidity: %d.%d %%", 
                dht.celsius, dht.celsius_min, dht.humidity, dht.humidity_min);

            /* Print Temperature */
            sprintf(tempstr, "Temperature: %d", dht.celsius);
            lcd_position (0, 0); 
            lcd_puts(tempstr); delay(5);

            /* Print humidity */
            sprintf(humstr, "Humidity: %d %%", dht.humidity);
            lcd_position (0, 1); 
            lcd_puts(humstr); delay(5);
            invalid_data = 1;
        }
        else 
        {
            slog(0, SLOG_ERROR, "Invalid data from Humidity/Temperature sensor");
            if (!invalid_data) 
            {
                lcd_position(0, 0);
                lcd_puts("Ivalid data");
                delay(5);
            }
        }

        /* Open lux relay */
        if (date.hour > uic.light_hour) open_relay(LEDS);
        else close_relay(LEDS);

        /* Open warm relay */
        if (dht.celsius < uic.celsius_min) 
        {
            open_relay(LIGHT);
            open_relay(COOLER);
            light_on = 1;
        }
        else 
        {
            close_relay(LIGHT);
            close_relay(COOLER);
            light_on = 0;
        }

        /* Open humidity relay */
        if (dht.humidity < uic.humidity_min) open_relay(WARTER);
        else close_relay(WARTER);

        /* Open cooling relay */
        if (dht.celsius > uic.celsius_max) 
        {
            open_relay(AIRCOOLER);
            open_relay(COOLER);
        }
        else
        {
            if (!light_on) close_relay(COOLER);
            close_relay(AIRCOOLER);
        }

        delay(3000);
    }

    return 0;
}
