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
    uint8 inputBuffer[40];
    uint8 bufferSizeCounter = 0;
    uint8 pressedKey;
    uint8 cursorIndex = 0;
    
    LCD_init();
    LCD_sendCommand(LCD_CMD_DISP_ON_CURSOR_ON);

    while(1){
        /* get the pressed key from the keypad and save it into pressedKey variable */
        pressedKey = KEYPAD_getPressedKey();
        /* go to the cursor location and display the pressed key if there is enough
         * space in the buffer */
        LCD_goToRowColumn(0, cursorIndex);
        if (pressedKey >= 0 && pressedKey <= 9) {
            /* Make sure the buffer is not full */
            if(bufferSizeCounter < 40){
                /* Display the pressed key on the LCD */
                LCD_displayCharacter(pressedKey + '0');
                /* save the pressed key into the input buffer */
                inputBuffer[cursorIndex] = pressedKey + '0';
            }
        } else {
            /* Make sure the buffer is not full */
            if(bufferSizeCounter < 40){
                /* Display the pressed key on the LCD */
                LCD_displayCharacter(pressedKey);
                /* save the pressed key into the input buffer */
                inputBuffer[cursorIndex] = pressedKey;                
            }

        }
        /* update cursor index*/
        cursorIndex++;
        /* update buffer size */
        bufferSizeCounter++;
        
        /* Shift the LCD to the right when it's full */
        if (cursorIndex > 16)
        {
            LCD_sendCommand(LCD_CMD_SHIFT_DISPLAY_LEFT);
        }
        _delay_ms(250);

        /* Display a warning message to the user indicating that the buffer is full */
        if(bufferSizeCounter >= 40){
            LCD_sendCommand(LCD_CMD_RETURN_HOME);
            LCD_displayStringRowColumn("Max Buffer!", 1, 0);
        }
    }
    return 0;
}
