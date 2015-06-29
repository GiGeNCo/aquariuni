/*
 * src/relay.h
 *
 *  Copyleft (C) 2015  IliaUni Robotics TeaM  
 * 
 * Simple program to drive SainSmart 8 Relay Module
 */


#include "stdinc.h"

/* Relay pins */
#define RELAYPIN1 24
#define RELAYPIN2 23
#define RELAYPIN3 22
#define RELAYPIN4 21
#define RELAYPIN5 28


/* 
 * init_relay - function initializes sain smart 8 
 * relay module and makes pins ready for digital write 
 */
void init_relay(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);


/* 
 * open_relay - Function opens relay. 
 * Argument is pin which we want to open.
 */
void open_relay(int pin);


/* 
 * close_relay - Function closes relay. 
 * Argument is pin which we want to close.
 */
void close_relay(int pin);