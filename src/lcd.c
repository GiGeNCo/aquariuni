/*
 * src/lcd.c
 *
 *  Copyleft (C) 2015  IliaUni Robotics TeaM  
 * 
 * Simple program to drive LCD device
 */

#include "stdinc.h"
#include "lcd.h"


/*
 * data_byte - Function sends bytes to lcd.
 * Argument is data which we want to send.
 */
void data_byte(uint8_t data)
{
    uint8_t i;

    for (i = 0; i < 8; ++i)
    {
        digitalWrite (i, (data & 1));
        data >>= 1;
    }
}


/* 
 * put_command - Function sends command to the lcd 
 * display. Arguments command which we want to send.
 */
void put_command(uint8_t command)
{
    digitalWrite(RS, 0);
    digitalWrite(STRB, 1);
    data_byte(command);
    delay(1);
    digitalWrite(STRB, 0);
    delay(1);
}


/* 
 * lcd_position - Function sets cursor position on 
 * lcd display. Arguments x and y are the cordinates.
 */
void lcd_position(int x, int y)
{
    uint8_t l2 = LCD_DGRAM;

    if (y == 1)
        l2 |= 0x40;

    l2 += x;
    put_command(l2);
}


/*
 * lcd_putchar - Function sends characters to the display.
 * Argument is cha rpointer which we want to send to lcd.
 */
void lcd_putchar(uint8_t data)
{
    digitalWrite(RS, 1);
    digitalWrite(STRB, 1);
    data_byte(data);
    delay(1);
    digitalWrite(STRB, 0);
    delay(1) ;
}


/*
 * lcd_puts - Function puts string on the display.
 * Argument string is string which we want to put.
 */
void lcd_puts(char *string)
{
    while(*string)
        lcd_putchar(*string++);
}


/* 
 * clear_lcd - This function clears lcd 
 * display when there is printed something.
 */
void clear_lcd() 
{
    /* Clear first line */
    lcd_position(0, 0); lcd_puts("                ");
    lcd_position(0, 1); lcd_puts("                ");
}


/* 
 * init_lcd - Function initializes lcd diplay and 
 * makes display ready to print something on it.
 */
void init_lcd(void)
{
    uint8_t i;

    for(i = 0; i < 8; ++i)
    {
        digitalWrite(i, 0);
        pinMode(i, OUTPUT);
    }

    digitalWrite(RS, 0);
    pinMode(RS, OUTPUT);

    digitalWrite(STRB, 1);
    pinMode(STRB, OUTPUT);
    
    delay(35);
    put_command(LCD_FUNC | LCD_FUNC_DL | LCD_FUNC_N);
    delay(5);
    put_command(LCD_FUNC | LCD_FUNC_DL | LCD_FUNC_N);
    delay(5);
    put_command (LCD_FUNC | LCD_FUNC_DL | LCD_FUNC_N);
    delay(5);

    put_command(LCD_ON_OFF | LCD_ON_OFF_D);
    delay(2);
    put_command(LCD_ENTRY | LCD_ENTRY_ID);
    delay(2);
    put_command (LCD_CDSHIFT | LCD_CDSHIFT_RL);
    delay(2);
    put_command(LCD_CLEAR);
    delay(5);
}