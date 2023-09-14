/*
 *  LCD_config.h
 *  Created on: Aug 20, 2023
 *  Author: Ayat Mohamed
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

// data port of LCD
#define LCD_DATA_PORT Port_C

// control port of LCD
#define LCD_CTRL_PORT Port_A

// register select (command or data)
#define LCD_RS_PIN Pin1

// read or write (read busy flag if i read with speed  higher then of LCD speed)
#define LCD_RW_PIN Pin2

// pin enable pulse high and low
#define LCD_E_PIN  Pin3

#endif /* LCD_CONFIG_H_ */
