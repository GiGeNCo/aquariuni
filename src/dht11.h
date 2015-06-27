/*
 * aquariuni/dht11.h
 *
 *  Copyleft (C)  2015  IliaUni Robotics TeaM
 *
 * Header for reading data from DHT11 Sensor with 
 * RaspberiPi Board. Use GCC and wiringPi library.
 */


/* Defs */ 
#define MAX_TIME 85
#define DHT11PIN 25
#define DHT11VAL 5


/* Sensor values */
typedef struct {
    int humidity;
    int celsius;
    int farenheit;
    int humidity_min;
    int celsius_min;
} DHTSensorValues;


/* 
 * init_dht_val - Initialize temperature and humidity sensor values 
 * Argument dhtsv is pointer of DHTSensorValues structure.
 */
void init_dht_val(DHTSensorValues *dhtsv);


/*
 * dht11_read_val - Function reads data from DHT11 
 * sensor and prints in terminal via printf() function,
 */   
int dht11_read_val(DHTSensorValues *dhtsv);
