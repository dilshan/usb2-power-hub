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

#include <xc.h>

#include "main.h"

int main() 
{
    unsigned char idleCounter = 0;
    unsigned char idleFlag = 0;
    
    initSystem();
    
    while(1)
    {
        usbFlag = PORTC & 0x20;
                
        if(usbFlag == 0x20)
        {
            // USB host connection is triggered and start to verify the connection.

            PORTC = 0x00;
            __delay_ms(500);
            usbFlag = PORTC & 0x20;
            
            if(usbFlag == 0x20)
            {
                // USB host connection is available and turn on the USB HUB.

                switchConfig = eeprom_read(0x00);
                liveServiceRoutine();
                
                // Host USB line is disconnected. Shutting down all USB ports.
                idleCounter = 0;
                idleFlag = 0;
                PORTC = 0x00;
            }
        }
        else 
        {
            // Blink power indicator in USB disconnected mode. 
            if((++idleCounter) == 10)
            {
                idleFlag = ~idleFlag;
                
                if(idleFlag == 0)
                {
                    PORTC = 0x00;
                    idleCounter = 0;
                }
                else
                {
                    PORTC = 0x10;
                    idleCounter = 8;
                }
            }
        }
        
        __delay_ms(100);
    }
}

void toggleStateBit(unsigned char togglePos, unsigned char *globalConfig, unsigned char *localConfig)
{
    if(((*globalConfig) & togglePos) == 0x00)
    {
        // Activate the specified bit.
        (*globalConfig) |= togglePos;
        (*localConfig) |= togglePos;
    }
    else
    {
        // Clear the specified bit.
        (*globalConfig) &= (~togglePos);
        (*localConfig) &= (~togglePos);
    }
}

void liveServiceRoutine()
{
    unsigned char buttonState = PORTA;
    unsigned char lastButtonState = buttonState;
    
    unsigned char resetState[4] = {0x00, 0x00, 0x00, 0x00};
    unsigned char buttonDownCounter[4] = {0x00, 0x00, 0x00, 0x00};
    
    // Restore USB ports to last state.
    switchConfig |= 0x10;
    unsigned char memSwitchConfig = switchConfig;
    
    while(usbFlag == 0x20)
    {
        PORTC = switchConfig;

        // Initiate reset cycle for USB port #1.  
        if(BUTTON_PRESSED(BUTTON_1) && ((memSwitchConfig & USB_PORT_1) == USB_PORT_1))
        {
            resetState[0] = RESET_LIMIT;
            switchConfig &= (~USB_PORT_1);
            buttonDownCounter[0] = 0;
        }
        
        // Initiate reset cycle for USB port #2.
        if(BUTTON_PRESSED(BUTTON_2) && ((memSwitchConfig & USB_PORT_2) == USB_PORT_2))
        {
            resetState[1] = RESET_LIMIT;
            switchConfig &= (~USB_PORT_2);
            buttonDownCounter[1] = 0;
        }
        
        // Initiate reset cycle for USB port #3.
        if(BUTTON_PRESSED(BUTTON_3) && ((memSwitchConfig & USB_PORT_3) == USB_PORT_3))
        {
            resetState[2] = RESET_LIMIT;
            switchConfig &= (~USB_PORT_3);
            buttonDownCounter[2] = 0;
        }
        
        // Initiate reset cycle for USB port #4.
        if(BUTTON_PRESSED(BUTTON_4) && ((memSwitchConfig & USB_PORT_4) == USB_PORT_4))    
        {
            resetState[3] = RESET_LIMIT;
            switchConfig &= (~USB_PORT_4);
            buttonDownCounter[3] = 0;
        }
        
        // Button #1 hold down counter to detect long presses.
        if(IS_BUTTON_DOWN(BUTTON_1, 0))
        {
            buttonDownCounter[0]++;
        }
        
        // Button #2 hold down counter to detect long presses.
        if(IS_BUTTON_DOWN(BUTTON_2, 1))
        {
            buttonDownCounter[1]++;
        }
        
        // Button #3 hold down counter to detect long presses.
        if(IS_BUTTON_DOWN(BUTTON_3, 2))
        {
            buttonDownCounter[2]++;
        }
        
        // Button #4 hold down counter to detect long presses.
        if(IS_BUTTON_DOWN(BUTTON_4, 3))
        {
            buttonDownCounter[3]++;
        }
        
        // Check reset timeout for each USB port, and restore port power. 
        if((resetState[0] | resetState[1] | resetState[2] | resetState[3]) != 0)
        {
            resetState[0] -= (resetState[0] != 0) ? 1 : 0;
            resetState[1] -= (resetState[1] != 0) ? 1 : 0;
            resetState[2] -= (resetState[2] != 0) ? 1 : 0;
            resetState[3] -= (resetState[3] != 0) ? 1 : 0;
            
            if(IS_PORT_ACTIVE(USB_PORT_1))
            {
                switchConfig |= (resetState[0] < 2) ? USB_PORT_1 : 0x00;
            }
            
            if(IS_PORT_ACTIVE(USB_PORT_2))
            {
                switchConfig |= (resetState[1] < 2) ? USB_PORT_2 : 0x00;
            }
            
            if(IS_PORT_ACTIVE(USB_PORT_3))
            {
                switchConfig |= (resetState[2] < 2) ? USB_PORT_3 : 0x00;
            }
            
            if(IS_PORT_ACTIVE(USB_PORT_4))
            {
                switchConfig |= (resetState[3] < 2) ? USB_PORT_4 : 0x00;
            }
        }
        
        // Long press handler to shutdown/activate USB port #1.
        if(buttonDownCounter[0] >= BUTTON_DOWN_TIME)
        {
            toggleStateBit(USB_PORT_1, &memSwitchConfig, &switchConfig);
            
            PORTC = switchConfig;
            eeprom_write(0x00, memSwitchConfig);
            
            while((buttonState & BUTTON_1) == 0x00)
            {
                __delay_ms(100);
                buttonState = PORTA;
            }
            
            buttonDownCounter[0] = 0;
        }
        
        // Long press handler to shutdown/activate USB port #2.
        if(buttonDownCounter[1] >= BUTTON_DOWN_TIME)
        {
            toggleStateBit(USB_PORT_2, &memSwitchConfig, &switchConfig);
            
            PORTC = switchConfig;
            eeprom_write(0x00, memSwitchConfig);
            
            while((buttonState & BUTTON_2) == 0x00)
            {
                __delay_ms(100);
                buttonState = PORTA;
            }
            
            buttonDownCounter[1] = 0;
        }
        
        // Long press handler to shutdown/activate USB port #3.
        if(buttonDownCounter[2] >= BUTTON_DOWN_TIME)
        {
            toggleStateBit(USB_PORT_3, &memSwitchConfig, &switchConfig);
            
            PORTC = switchConfig;
            eeprom_write(0x00, memSwitchConfig);
            
            while((buttonState & BUTTON_3) == 0x00)
            {
                __delay_ms(100);
                buttonState = PORTA;
            }
            
            buttonDownCounter[2] = 0;
        }
        
        // Long press handler to shutdown/activate USB port #4.
        if(buttonDownCounter[3] >= BUTTON_DOWN_TIME)
        {
            toggleStateBit(USB_PORT_4, &memSwitchConfig, &switchConfig);
            
            PORTC = switchConfig;
            eeprom_write(0x00, memSwitchConfig);
            
            while((buttonState & BUTTON_4) == 0x00)
            {
                __delay_ms(100);
                buttonState = PORTA;
            }
            
            buttonDownCounter[3] = 0;
        }
        
        lastButtonState = buttonState;
        __delay_ms(100);
        
        buttonState = PORTA;
        usbFlag = PORTC & 0x20;
    }
}

void initSystem()
{
    // Initialize MCU peripherals to known state.
    OPTION_REG = 0x00;
    CMCON = 0x07;
    
    TRISC = 0xE0;
    PORTC = 0x00;
    
    TRISA = 0xFF;
    PORTA = 0x00;
    WPUA = 0xFF;
    
    // Initialize all global variables to known state.
    powerControlStatus = PORTC;
    usbFlag = PORTC & 0x20;
    switchConfig = 0x0F;
}