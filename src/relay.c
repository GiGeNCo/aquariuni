/*
 * src/relay.c
 *
 *  Copyleft (C) 2015  IliaUni Robotics TeaM  
 * 
 * Simple program to drive SainSmart 8 Relay Module
 */


#include "stdinc.h"
#include "relay.h"

/* 
 * open_relay - Function opens relay. 
 * Argument is pin which we want to open.
 */
void open_relay(int pin) { digitalWrite(pin, 0); }


/* 
 * close_relay - Function closes relay. 
 * Argument is pin which we want to close.
 */
void close_relay(int pin) { digitalWrite(pin, 1); }


/* 
 * init_relay - function initializes sain smart 8 
 * relay module and makes pins ready for digital write 
 */
void init_relay(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
    /* Initialize pins */
    if (p1) { pinMode(p1, OUTPUT); close_relay(p1); }
    if (p2) { pinMode(p2, OUTPUT); close_relay(p2); }
    if (p3) { pinMode(p3, OUTPUT); close_relay(p3); }
    if (p4) { pinMode(p4, OUTPUT); close_relay(p4); }
    if (p5) { pinMode(p5, OUTPUT); close_relay(p5); }
    if (p6) { pinMode(p6, OUTPUT); close_relay(p6); }
    if (p7) { pinMode(p7, OUTPUT); close_relay(p7); }
    if (p8) { pinMode(p8, OUTPUT); close_relay(p8); }
}