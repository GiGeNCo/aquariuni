/*
 * src/dht11.c
 *
 *  Copyleft (C)  2015  IliaUni Robotics TeaM
 *
 * Source for reading data from DHT11 Sensor with 
 * RaspberryPi Board. Use GCC and wiringPi library.
 */


#include "stdinc.h"
#include "dht11.h"


/* Initialize sensor values */
int dht11_val[DHT11VAL] = {0, 0, 0, 0, 0};


/* 
 * init_dht_val - Initialize temperature and humidity sensor values 
 * Argument dhtsv is pointer of DHTSensorValues structure.
 */
void init_dht_val(DHTSensorValues *dhtsv) 
{
    dhtsv->humidity = 0;
    dhtsv->celsius = 0;
    dhtsv->farenheit = 0;
    dhtsv->humidity_min = 0;
    dhtsv->celsius_min = 0;
}


/*
 * dht11_read_val - Function reads data from DHT11 
 * sensor and prints in terminal via printf() function,
 */   
int dht11_read_val(DHTSensorValues *dhtsv)
{
    /* Used variables */
    uint8_t lststate = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;
    float farenheit;

    /* Make sure sensor values ar zero */
    for(i=0; i<DHT11VAL; i++) dht11_val[i]=0;

    /* Initialize sensors */
    pinMode(DHT11PIN,OUTPUT);
    digitalWrite(DHT11PIN,LOW);
    delay(18);
    digitalWrite(DHT11PIN,HIGH);
    delayMicroseconds(40);
    pinMode(DHT11PIN,INPUT);

    /* Start data reading */
    for(i=0; i<MAX_TIME; i++)
    {
        counter = 0;
        while(digitalRead(DHT11PIN)==lststate)
        {
            counter++;
            delayMicroseconds(1);
            if(counter == 255) break;  
        }

        /* Read digital data */
        lststate = digitalRead(DHT11PIN);
        if(counter == 255) break;

        /* Ignore top 3 transistions */
        if((i >= 4) && (i%2 == 0))
        {
            dht11_val[j/8]<<=1;
            if(counter > 16) dht11_val[j/8] |= 1;
            j++;
        }
    }

    /* Verify cheksum and print the verified data */
    if((j>=40) && (dht11_val[4] == ((dht11_val[0] + dht11_val[1] + dht11_val[2] + dht11_val[3])& 0xFF)))
    {
        /* Calculate farenheit */
        farenheit = dht11_val[2]*9./5.+32;

        /* Save values */
        dhtsv->humidity = dht11_val[0];
        dhtsv->humidity_min = dht11_val[1];
        dhtsv->celsius = dht11_val[2];
        dhtsv->celsius_min = dht11_val[3];
        dhtsv->farenheit = farenheit;

        return 1;
    }
    
    return 0;
}