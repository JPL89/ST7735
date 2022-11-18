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

#include <xc.h>

#include "st7735.h"

#define _NOOPERATION() __asm__ __volatile__("nop")

void ST7735_Write(unsigned char data)
{
    for(unsigned char mask=0x80; mask; mask >>=1)
    {
        ST7735_CLK_LOW;	
        if(data & mask) ST7735_DIO_HIGH; else ST7735_DIO_LOW;		
        ST7735_CLK_HIGH;
    }
}

void ST7735_Command(unsigned char cmd)
{
    ST7735_DC_LOW;
    ST7735_CS_LOW;
    ST7735_Write( cmd);
    ST7735_CS_HIGH;
}

void ST7735_Write_8bits(unsigned char data)
{
    ST7735_DC_HIGH;
    ST7735_CS_LOW;
    ST7735_Write( data );
    ST7735_CS_HIGH;
}

void ST7735_Write_16bits(int data)
{
    ST7735_DC_HIGH;
    ST7735_CS_LOW;
    ST7735_Write( (unsigned char) (data >> 8 & 0xFF) );
    ST7735_Write( (unsigned char) (data & 0xFF) );
    ST7735_CS_HIGH;
}

void ST7735_Set_Window(int XS, int XE, int YS, int YE)
{
    // 80X160 #VERTICAL MODE
    //XS += 24;
    //XE += 24;
    
    // 80X160 HORIZONTAL MODE
    //YS += 24;
    //YE += 24;
    
    ST7735_Command(CASET);
    ST7735_Write_16bits(XS);
    ST7735_Write_16bits(XE);
    
    ST7735_Command(RASET);
    ST7735_Write_16bits(YS);
    ST7735_Write_16bits(YE);
        
    ST7735_Command(RAMWR);
}

void ST7735_Set_Pixel(int x, int y, int color)
{
    ST7735_Set_Window(x, y, y, y);
    ST7735_Write_16bits(color);
}


void ST7735_Draw_Image_16bits(const unsigned char *buffer, int x, int y, int w, int h)
{    

    ST7735_Set_Window(x, x+w-1, y, y+h-1);

    for(int i=0; i<(w*h)*2; i++) 
    {
        ST7735_Write_8bits(buffer[i]) ;    
    }
}

void ST7735_Fill(int color)
{   
    ST7735_Set_Window(0, ST7735_WIDTH-1, 0, ST7735_HEIGHT-1);

    unsigned short GEOMETRY = (ST7735_WIDTH * ST7735_HEIGHT);
    
    for (unsigned short i=0; i<GEOMETRY; i++)
    {
        ST7735_Write_16bits(color);
    }
}

void ST7735_BgColor(int x, int y, int size_W, int size_H, int color)
{
        ST7735_Set_Window(x, x+size_W-1, y, y+size_H-1);

        for (unsigned int i=0; i<(size_W*size_H); i++)
        {
            ST7735_Write_16bits(color);
        }
}

void ST7735_DrawRectangle(int x, int y, int width, int height, int color)
{
    unsigned char k = 0;
    unsigned char i = 0;

    for(i=0; i<height; i++)
    {
        for(k=0; k<width; k++)
        {
            if( i%(height-1) == 0)
            {
                ST7735_Set_Pixel(x + k, y + i, color);
            }

            if( k%(width-1) == 0)
            {
                ST7735_Set_Pixel(x + k, y + i, color);
            }
        }
    }
}

void ST7735_DrawRectangleA(int x, int y, int area, int color)
{
    for(unsigned char i=0; i<(area + 1); i++)
    {
        ST7735_Set_Pixel(x, y + i, color);
        ST7735_Set_Pixel(x + i, y, color);
        ST7735_Set_Pixel(x + i, y + area, color);
        ST7735_Set_Pixel(x + area + 1, y + i, color);
    }
}

void ST7735_Draw_Pixel_Image(
const unsigned char *Image_Buffer,
int x, int y,
int w, int h, int Color)
{
	
}

void ST7735_Char(int dt, const unsigned long Font[], int color)
{
    int ff = 5; // FONT FRAMEHEADER SIZE
    int fo = 0; // FONT OFFSET	
    int fw = (int) Font[fo++]; // FONT WIDTH
    int fh = (int) Font[fo++]; // FONT HEIGHT
    int fs = (int) Font[fo++]; // FONT START CHAR
    int fd = (int) Font[fo++]; // LOOKUP TABLE SIZE
    int fr = (int) Font[fo++]; // RESERVED 
    
    fo += fd;
    
    unsigned long ch = 0x00000000;
    int y = 0;
    
    for(int col = 0; col < fw; col++ )
    {
        y = 0;
        
        ch = Font[ ( ( dt - fs ) * fw ) + fo + col ];
        
        for(unsigned long row = 1; row; row <<= 1)
        {
            if (ch & row)
            {      
                ST7735_Set_Pixel( (int) ST7735_CURSOR_X + col, (int) ST7735_CURSOR_Y + y, color );                
            }
            
            y++;
        }
    }
    
    ST7735_CURSOR_X +=  (int)  Font[ ff + ( dt - fs ) ]; // GET NEW X PPOSITION
    ST7735_CURSOR_X += 1; // ONE SETP
}

void ST7735_String_XY(const char *data, int x, int y, const unsigned long Font[], int Color)
{
    ST7735_CURSOR_X = x;
    ST7735_CURSOR_Y = y;

    while(*data)
    {
        ST7735_Char(*data++, Font, Color);
    }
}

void ST7735_String(const char *data, const unsigned long Font[], int Color)
{
    while(*data)
    {
        ST7735_Char(*data++, Font, Color);
    }
}

void ST7735_Int_XY(long num, int x, int y, const unsigned long Font[], int color)
{	
    ST7735_CURSOR_X = x;
    ST7735_CURSOR_Y = y;
    
    if( num == 0) {
        ST7735_Char( 48, Font, color);
        return;
    }
    
    long a = num;
    long b = 1;

    while(a--) {
        a /= 10;	// e.g 10000, 1000, 100, 10, 1
        b *= 10;	// e.g 1, 10, 100, 10000, 100000
    }

    b /= 10;

    while(b){
        ST7735_Char( (num / b % 10) + 48, Font, color);
        b /= 10;
    }
}

void ST7735_Int(long num, const unsigned long Font[], int color)
{
    if( num == 0) {
        ST7735_Char( 48, Font, color);
        return;
    }
    
    long a = num;
    long b = 1;

    while(a--) {
        a /= 10;	// e.g 10000, 1000, 100, 10, 1
        b *= 10;	// e.g 1, 10, 100, 10000, 100000
    }

    b /= 10;

    while(b){
        ST7735_Char( (num / b % 10) + 48, Font, color);
        b /= 10;
    }	
}

void ST7735_Float_XY(double f, long decimal, int x, int y, const unsigned long Font[], int color)
{
    if(decimal > 5) decimal = 5; // e.g 100000
    
    long cd = 1;
    while(decimal--) cd*=10;
	
    long i = (long) f;
    f = (double) (f - i);
    f = (double) ( f * cd);
    long ii = (long) f;
    
    ST7735_Set_XY(x, y);
    ST7735_Int( (long) i, Font, color); 
    ST7735_String(".", Font, color); 
    ST7735_Int( ii, Font, color); 
}

void ST7735_Float(double f, long decimal, const unsigned long Font[], int color)
{
   if(decimal > 5) decimal = 5; // e.g 100000
    
    long cd = 1;
    while(decimal--) cd*=10;
	
    long i = (long) f;
    f = (double) (f - i);
    f = (double) ( f * cd);
    long ii = (long) f;
    
    ST7735_Int( (long) i, Font, color); 
    ST7735_String(".", Font, color); 
    ST7735_Int( ii, Font, color); 	
}

void ST7735_Set_XY(int x, int y)
{
    ST7735_CURSOR_X = x;
    ST7735_CURSOR_Y = y;
}
 
void ST7735_Init(void)
{
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISC3 = 0;
    TRISC4 = 0; 

    ST7735_CS_HIGH;

    _NOOPERATION();		  
    ST7735_RS_HIGH;
     _NOOPERATION();
    ST7735_RS_LOW;
    _NOOPERATION();
    ST7735_RS_HIGH;
    _NOOPERATION();
	        
    //---------------------------------------------------------
    ST7735_Command(ST77XX_SLPOUT);//Sleep exit

    //---------------------------------------------------------
    ST7735_Command(ST7735_DISPOFF);//DISPOFF

    //---------------------------------------------------------
    ST7735_Command(ST7735_FRMCTR1);
    ST7735_Write_8bits(0x01); 
    ST7735_Write_8bits(0x2C); 
    ST7735_Write_8bits(0x2D);

    //---------------------------------------------------------
    ST7735_Command(ST7735_FRMCTR2);
    ST7735_Write_8bits(0x01); 
    ST7735_Write_8bits(0x2C); 
    ST7735_Write_8bits(0x2D);

    //---------------------------------------------------------
    ST7735_Command(ST7735_FRMCTR3);
    ST7735_Write_8bits(0x01); 
    ST7735_Write_8bits(0x2C); 
    ST7735_Write_8bits(0x2D);
    ST7735_Write_8bits(0x01); 
    ST7735_Write_8bits(0x2C); 
    ST7735_Write_8bits(0x2D);

    //---------------------------------------------------------
    ST7735_Command(ST7735_INVCTR); //Column inversion
    ST7735_Write_8bits(0x07);

   //---------------------------------------------------------
    ST7735_Command(ST7735_PWCTR1);
    ST7735_Write_8bits(0xA2); 
    ST7735_Write_8bits(0x02); 
    ST7735_Write_8bits(0x84);

    //---------------------------------------------------------
    ST7735_Command(ST7735_PWCTR2); 
    ST7735_Write_8bits(0xC5);

    //---------------------------------------------------------
    ST7735_Command(ST7735_PWCTR3);
    ST7735_Write_8bits(0x0A); 
    ST7735_Write_8bits(0x00);

    //---------------------------------------------------------
    ST7735_Command(ST7735_PWCTR4);
    ST7735_Write_8bits(0x8A); 
    ST7735_Write_8bits(0x2A);

    //---------------------------------------------------------
    ST7735_Command(ST7735_PWCTR5);
    ST7735_Write_8bits(0x8A); 
    ST7735_Write_8bits(0xEE);

    //---------------------------------------------------------
    ST7735_Command(ST7735_VMCTR1); //VCOM
    ST7735_Write_8bits(0x0E);

    //---------------------------------------------------------
    ST7735_Command(ST7735_GMCTRP1);
    ST7735_Write_8bits(0x02);
    ST7735_Write_8bits(0x1c);
    ST7735_Write_8bits(0x07);
    ST7735_Write_8bits(0x12);
    ST7735_Write_8bits(0x37);
    ST7735_Write_8bits(0x32);
    ST7735_Write_8bits(0x29);
    ST7735_Write_8bits(0x2d);
    ST7735_Write_8bits(0x29);
    ST7735_Write_8bits(0x25);
    ST7735_Write_8bits(0x2b);
    ST7735_Write_8bits(0x39);
    ST7735_Write_8bits(0x00);
    ST7735_Write_8bits(0x01);
    ST7735_Write_8bits(0x03);
    ST7735_Write_8bits(0x10);
    
    //---------------------------------------------------------
    ST7735_Command(ST7735_GMCTRN1);
    ST7735_Write_8bits(0x03); 
    ST7735_Write_8bits(0x1d);
    ST7735_Write_8bits(0x07); 
    ST7735_Write_8bits(0x06);
    ST7735_Write_8bits(0x2e); 
    ST7735_Write_8bits(0x2c);
    ST7735_Write_8bits(0x29); 
    ST7735_Write_8bits(0x2d);
    ST7735_Write_8bits(0x2e); 
    ST7735_Write_8bits(0x2e);
    ST7735_Write_8bits(0x37); 
    ST7735_Write_8bits(0x3f);
    ST7735_Write_8bits(0x00); 
    ST7735_Write_8bits(0x00);
    ST7735_Write_8bits(0x02); 
    ST7735_Write_8bits(0x10);

    //---------------------------------------------------------
    ST7735_Command(ST77XX_CASET);
    ST7735_Write_8bits(0x00);
    ST7735_Write_8bits(0x00);
    ST7735_Write_8bits(0x00);
    ST7735_Write_8bits(128);

    //---------------------------------------------------------
    ST7735_Command(ST77XX_RASET);
    ST7735_Write_8bits(0x00);
    ST7735_Write_8bits(0x00);
    ST7735_Write_8bits(0x00);
    ST7735_Write_8bits(160);
    
    //---------------------------------------------------------
    ST7735_Command(ST7735_COLMOD);
    ST7735_Write_8bits( 0x05 ); 

    //---------------------------------------------------------
    // MADCTL
    ST7735_Command(ST77XX_MADCTL); 
    
    // VERTICAL #1
    // MV = 0
    // MX = 0
    // MY = 0
    // RGB = 1
    // ST7735_Write_8bits( 0x08 );
    
    // VERTICAL #2
    // MV = 0
    // MX = 1
    // MY = 1
    // RGB = 1
    //ST7735_Write_8bits( 0xC8 ); // USED
    
    // HORIZONTAL #1
    // MV = 1
    // MX = 1
    // MY = 0
    // RGB = 1
    // 128x160 display: 0X68, 80x160 display: 0X60
    ST7735_Write_8bits( 0x60 ); 
    
    // HORIZONTAL #2
    // MV = 1
    // MX = 0
    // MY = 1
    // RGB = 1
    //ST7735_Write_8bits( 0xA0 ); 
     
    //---------------------------------------------------------
    ST7735_Command(ST77XX_NORON); // NORON

    //---------------------------------------------------------
    ST7735_Command(ST77XX_DISPON);//Display on
}

