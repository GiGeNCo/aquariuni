/*
 * aquariuni/humidity.c
 *
 *  Copyleft (C)  2015  IliaUni Robotics TeaM
 *
 * Source for reading data from DHT11 Sensor with 
 * RaspberiPi Board. Use GCC and wiringPi library.
 */


#include <wiringPi.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h>
#include <wiringPi.h>  

/* Defs */ 
#define MAX_TIME 85  
#define DHT11PIN 7
#define DHT11VAL 5

/* Initialize sensor values */
int dht11_val[DHT11VAL] = {0, 0, 0, 0, 0};  


/*
 * dht11_read_val - Function reads data from DHT11 
 * sensor and prints in terminal via printf() function,
 */   
void dht11_read_val()  
{
    /* Used variables */
    uint8_t lststate=HIGH;  
    uint8_t counter=0;  
    uint8_t j=0,i;  
    float farenheit;

    /* Make sure sensor values ar zero */
    for(i=0; i<DHT11VAL; i++)  
        dht11_val[i]=0;  

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
            if(counter==255)  
                break;  
        }

        /* Read digital data */
        lststate=digitalRead(DHT11PIN);  
        if(counter==255)  
            break;  

        /* Ignore top 3 transistions */
        if((i >= 4) && (i%2 == 0))
        {  
            dht11_val[j/8]<<=1;  
            if(counter > 16) dht11_val[j/8] |= 1;  
            j++;  
        }  
    }  
    
    /* Verify cheksum and print the verified data */
    if((j>=40) && (dht11_val[4]==((dht11_val[0] + dht11_val[1] + dht11_val[2] + dht11_val[3])& 0xFF)))  
    {  
        farenheit=dht11_val[2]*9./5.+32;  
        printf("Humidity: %d.%d %% Temperature: %d.%d *C (%.1f *F)\n",
            dht11_val[0], dht11_val[1], dht11_val[2], dht11_val[3], farenheit);  
    }  
    else  
    printf("Invalid Data!!\n");  
}


/* Main function */
int main(void)  
{
    int ret;

    /* Set up writing pin */
    ret = wiringPiSetup();

    /* Check status */
    if(ret == -1) exit(1);  

    /* Main loop (never ends) */
    while(1)  
    {
        /* Read dara */
        dht11_read_val();  
        delay(3000);  
    }

    return 0;  
}  
