// @File		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		11/10/22
//
//
// Copyright (C) 2021  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#include "utils.h"

#include "st7735.h"
#include "font_11x10.h"
#include "font_16x16.h"
#include "font_5x7.h"
#include "FontN.h"
#include "Icons.h"

int main(void) 
{
    __delay_ms(1000);

    // CLEAR PORTS
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;

    // CLEAR DATA LATCHES
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    // A/D PORT CONFIGURAION CONTROL BIT
    // (0x0F) DIGITAL I/O
    ADCON1 = 0x0F;

    // TURN OFF THE COMPARATORS
    CMCON = 0x07;

    ST7735_Init();

    ST7735_BgColor(0, 0, 128, 160, RGB(255, 255, 255));

    TRISB5 = 1;
    
    while (1) 
	{
        ;
    }
}
