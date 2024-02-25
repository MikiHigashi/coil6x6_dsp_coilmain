// 受信機メインdsPIC
#define FCY 69784687UL
#include <libpic30.h>
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>
#include "soft_i2c.h"
#include "lcd_i2c.h"


//char buf[32];
uint8_t n_on = 0; // TRIG_ON 連続ON回数 
uint8_t n_off = 0; // TRIG_ON 連続OFF回数 
uint8_t trigger = 0; // 安定化処理後のトリガー状態
uint8_t trigger0 = 0; // 安定化処理後のトリガー状態の直前状態


// コイルガン発射
void fire(void) {
    COIL01_SetLow();
    __delay_us(500);    
    COIL02_SetLow();

    __delay_ms(20);    
    COIL01_SetHigh();
    COIL02_SetHigh();
    COIL03_SetHigh();
    COIL04_SetHigh();
    COIL05_SetHigh();
    COIL06_SetHigh();
    COIL07_SetHigh();
    COIL08_SetHigh();
    COIL09_SetHigh();
    COIL10_SetHigh();
    COIL11_SetHigh();
    COIL12_SetHigh();
    COIL13_SetHigh();
    COIL14_SetHigh();
    COIL15_SetHigh();
    COIL16_SetHigh();
}


int main(void) {
    // initialize the device
    SYSTEM_Initialize();

    //__delay_ms(100); // I2C バス安定化待ち    
    //LCD_i2c_init(8);
    //LCD_i2C_cmd(0x80);
    //LCD_i2C_data("ABCDE");

    while (1)
    {
        WATCHDOG_TimerClear();
        if (TRIG_IN_GetValue()) {
            n_on ++;
            if (n_on > 5) {
                n_on = 5;
                trigger = 1;
            }
            n_off = 0;
        }
        else {
            n_off ++;
            if (n_off > 10) {
                n_off = 10;
                trigger = 0;
            }
            n_on = 0;
        }

        if (trigger) {
            if (trigger0 == 0) {
                fire();                
            }
        }
        trigger0 = trigger;
        __delay_ms(10);    
    }
    return 1; 
}
/**
 End of File
*/

