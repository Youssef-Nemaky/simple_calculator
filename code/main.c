/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 27/11/2021
* Name: main.c 
==============================================================================
*/

/*
==============================================================================
*                            Include Files
==============================================================================
*/
/* HAL Drivers */
#include "HAL/LCD_Driver/lcd.h"
#include "HAL/Keypad_Driver/keypad.h"
/* MCAL Drivers */
#include "MCAL/Gpio_Driver/gpio.h"

/*
==============================================================================
*                               Definitions
==============================================================================
*/

int main(void){
    uint8 pressedKey;
    uint8 counter = 0;
    LCD_init();
    LCD_sendCommand(LCD_CMD_DISP_ON_CURSOR_BLINK);

    while(1){
        pressedKey = KEYPAD_getPressedKey();
        counter++;
        if(pressedKey >= 0 && pressedKey <= 9){
            LCD_displayCharacter(pressedKey + '0');
        } else {
            LCD_displayCharacter(pressedKey);
        }
        _delay_ms(250);
        if(counter >= 16){
            LCD_sendCommand(LCD_CMD_SHIFT_DISPLAY_LEFT);
        } 
        if (counter == 40){
            counter = 0;
            LCD_sendCommand(LCD_CMD_RETURN_HOME);
            LCD_goToRowColumn(1,0);
        }

    }
    return 0;
}
