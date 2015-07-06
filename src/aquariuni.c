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


/* System flags */
typedef struct {
    short invalid_data;
    short aircooler_on;
    short cooler_on;
    short water_on;
    short light_on;
    short leds_on;
} SystemFlags;


/*
 * clean_up - Function closes everything 
 * if there is something error occured. 
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


/*
 * init_flags - Initialize system flags. Function sets 
 * zero values for each SystemFlags structure members.
 */
void init_flags(SystemFlags *flags) 
{
    flags->invalid_data = 0;
    flags->aircooler_on = 0;
    flags->cooler_on = 0;
    flags->water_on = 0;
    flags->light_on = 0;
    flags->leds_on = 0;
}


/* Main function */
int main(void)
{
    /* Used variables */
    UserInputConfig uic;
    DHTSensorValues dht;
    SystemFlags flags;
    SystemDate date;
    char tempstr[128];
    char humstr[128];
    int status;

    /* Greet users */
    greet("AquariUni");

    /* Initialize logger */
    init_slog("aquariuni", CONFIG_FILE, 3);

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
    init_flags(&flags);
    init_uic(&uic);
    init_dht_val(&dht);
    init_lcd(); sleep(1);

    /* Initialize relays */
    init_relay(RELAYPIN1, RELAYPIN2, RELAYPIN3, RELAYPIN4, RELAYPIN5, 0,0,0);

    /* Parse config file */
    status = parse_user_config(CONFIG_FILE, &uic);
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
            flags.invalid_data = 1;
        }
        else 
        {
            slog(0, SLOG_ERROR, "Invalid data from Humidity/Temperature sensor");
            if (!flags.invalid_data) 
            {
                lcd_position(0, 0);
                lcd_puts("Ivalid data");
                delay(5);
            }
        }

        /* Open lux relay */
        if (date.hour > uic.light_hour) 
        {
            open_relay(LEDS);
            if (!flags.leds_on)
                slog(0, SLOG_INFO, "Enabling leds for light");

            /* Set flag */
            flags.leds_on = 1;
        }
        else 
        {
            close_relay(LEDS);
            if (flags.leds_on)
                slog(0, SLOG_INFO, "Enabling leds for light");

            /* Set flag */
            flags.leds_on = 1;
        }

        /* Open warm relay */
        if (dht.celsius < uic.celsius_min) 
        {
            open_relay(LIGHT);
            open_relay(COOLER);
            if (!flags.light_on)
                slog(0, SLOG_INFO, "Enabling warming system");

            /* Set flags */
            flags.light_on = 1;
            flags.cooler_on = 1;
        }
        else 
        {
            close_relay(LIGHT);
            close_relay(COOLER);
            if (flags.light_on)
                slog(0, SLOG_INFO, "Disabling warming system");

            /* Set flags */
            flags.light_on = 0;
            flags.cooler_on = 0;
        }

        /* Open humidity relay */
        if (dht.humidity < uic.humidity_min) 
        {
            open_relay(WARTER);
            if (!flags.water_on)
                slog(0, SLOG_INFO, "Enabling water system");

            /* Set flag */
            flags.water_on = 1;
        }
        else 
        {
            close_relay(WARTER);
            if (flags.water_on)
                slog(0, SLOG_INFO, "Disabling water system");

            /* Set flag */
            flags.water_on = 0;
        }

        /* Open cooling relay */
        if (dht.celsius > uic.celsius_max) 
        {
            open_relay(AIRCOOLER);
            open_relay(COOLER);
            if (!flags.aircooler_on)
                slog(0, SLOG_INFO, "Enabling cooling system");

            /* Set flags */
            flags.aircooler_on = 1;
            flags.cooler_on = 1;
        }
        else
        {
            if (!flags.light_on) 
            {
                close_relay(COOLER);
                flags.cooler_on = 0;
            }

            close_relay(AIRCOOLER);
            if (flags.aircooler_on)
                slog(0, SLOG_INFO, "Disabling cooling system");

            /* Set flag */
            flags.aircooler_on = 0;
        }

        /* Parse config values again */
        parse_user_config(CONFIG_FILE, &uic);

        /* Delay */
        delay(3000);
    }

    return 0;
}
