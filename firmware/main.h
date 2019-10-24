//***********************************************************************************
// Copyright (c) 2019 Dilshan R Jayakody. [jayakody2000lk@gmail.com]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of 
// this software and associated documentation files (the "Software"), to deal in the 
// Software without restriction, including without limitation the rights to use, 
// copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
// Software, and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all 
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//***********************************************************************************

#ifndef MAIN_H
#define	MAIN_H

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA3/MCLR pin function select (RA3/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

// MCU is configured for internal 4MHz oscillator.
#define _XTAL_FREQ 4000000

#define RESET_LIMIT 30
#define BUTTON_DOWN_TIME    20

#define USB_PORT_1  0x01
#define USB_PORT_2  0x02
#define USB_PORT_3  0x04
#define USB_PORT_4  0x08

#define BUTTON_1    0x01
#define BUTTON_2    0x02
#define BUTTON_3    0x04
#define BUTTON_4    0x10

#define BUTTON_PRESSED(x) (((buttonState & x) == x) && ((lastButtonState & x) == 0x00))
#define IS_BUTTON_DOWN(x, i) (((buttonState & x) == 0x00) && (buttonDownCounter[i] < 0xFF) && (resetState[i] == 0))
#define IS_PORT_ACTIVE(x) ((memSwitchConfig & x) == x)

unsigned char powerControlStatus;
unsigned char switchConfig;
unsigned char usbFlag;

void initSystem(void);
void liveServiceRoutine(void);
void toggleStateBit(unsigned char togglePos, unsigned char *globalConfig, unsigned char *localConfig);

#endif	/* MAIN_H */

