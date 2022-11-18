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

#ifndef ST7735_H_
#define ST7735_H_

// SELECT DISPLAY MODE
// 80x160
//#define ST7735_80x160_VERTICAL
//#define ST7735_80x160_HORIZONTAL

// 128x160: 1.8 inch
//#define ST7735_128x160_VERTICAL
//#define ST7735_128x160_HORIZONTAL

#define SCREEN_WIDTH	128
#define SCREEN_HEIGHT	160

#define ST7735_WIDTH SCREEN_WIDTH
#define ST7735_HEIGHT SCREEN_HEIGHT

#define ST7735_CS_LOW                   PORTCbits.RC0=0
#define ST7735_CS_HIGH                  PORTCbits.RC0=1

#define ST7735_DC_LOW                   PORTCbits.RC1=0
#define ST7735_DC_HIGH                  PORTCbits.RC1=1

#define ST7735_RS_LOW                   PORTCbits.RC2=0
#define ST7735_RS_HIGH                  PORTCbits.RC2=1

#define ST7735_DIO_LOW                  PORTCbits.RC3=0
#define ST7735_DIO_HIGH                 PORTCbits.RC3=1

#define ST7735_CLK_LOW                  PORTCbits.RC4=0
#define ST7735_CLK_HIGH                 PORTCbits.RC4=1

#define CASET 0x2A	// Column Address Set
#define RASET 0x2B	// Row Address Set
#define RAMWR 0x2C	// Memory write


// ST7735 COLORS 565
#define RGB(r, g, b)			(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

// ST7735 COLOR_RGB
#define ST7735_COLOR_RED		RGB(255,0,0)
#define ST7735_COLOR_YELLOW		RGB(255,255,0)
#define ST7735_COLOR_BLACK		RGB(0,0,0)
#define ST7735_COLOR_WHITE		RGB(255,255,255)
#define ST7735_COLOR_ORANGE		RGB(255,165,0)
#define ST7735_COLOR_BLUE		RGB(0,0,255)
#define	ST7735_COLOR_AQUA		RGB(0,255,255)
#define ST7735_COLOR_LIGHT_GRAY		RGB(211,211,211)
#define ST7735_COLOR_LIME		RGB(0,255,0)
#define ST7735_COLOR_GAINSBORO		RGB(220,220,220)
#define ST7735_COLOR_SILER		RGB(192,192,192)
#define ST7735_COLOR_GREEN		RGB(0,128,0)
#define ST7735_COLOR_NAVY		RGB(0,0,128)
#define ST7735_COLOR_GRAY		RGB(128,128,128)
#define ST7735_COLOR_STATE_GRAY		RGB(112,128,144)
#define ST7735_COLOR_DIM_GRAY		RGB(105,105,105)
#define ST7735_COLOR_MARRON		RGB(128,0,0)
#define ST7735_COLOR_GOLDEN_ROD		RGB(218,165,32)
#define ST7735_COLOR_DARK_ORANGE	RGB(255,140,0)
#define ST7735_COLOR_PALE_GOLDEN_ROD	RGB(238,232,170)
#define ST7735_COLOR_KHAKI		RGB(240,230,140)
#define ST7735_COLOR_OLIVE		RGB(128,128,0)
#define ST7735_COLOR_YELLOW_GREEN	RGB(154,205,50)
#define ST7735_COLOR_SKY_BLUE		RGB(135,206,235)
#define ST7735_COLOR_TEAL		RGB(0,128,128)
#define ST7735_COLOR_BISQUE		RGB(255,228,196)
#define ST7735_COLOR_BEIGE		RGB(245,245,220)
#define ST7735_COLOR_WHEAT		RGB(245,222,179)
#define ST7735_COLOR_STATE_GRAY		RGB(112,128,144)
#define ST7735_COLOR_DIM_GRAY		RGB(105,105,105)
#define ST7735_COLOR_DARK_GRAY		RGB(169,169,169)
#define ST7735_COLOR_WHITE_SMOKE	RGB(245,245,245)


// MADCTL
#define ST7735_MADCTL_DEFAULT 0x00
#define ST7735_MADCTL_Y_MIRROR 0x20
#define ST7735_MADCTL_X_MIRROR 0x40
#define ST7735_MADCTL_XY_MIRROR 0x60
#define ST7735_MADCTL_XY_EXCHANGE 0x80
#define ST7735_MADCTL_XY_EXCHANGE_Y_MIRROR 0xA0
#define ST7735_MADCTL_XY_EXCHANGE_X_MIRROR 0xC0
#define ST7735_MADCTL_XY_EXCHANGE_XY_MIRROR 0xE0

// COLMOD
#define ST7735_COLMOD_12_BITS 0x03
#define ST7735_COLMOD_16_BITS 0x05
#define ST7735_COLMOD_18_BITS 0x06
#define ST7735_COLMOD_NOT_USED 0x07


#define ST7789_Cmd_MADCTL_MY 0x80
#define ST7789_Cmd_MADCTL_MX 0x40
#define ST7789_Cmd_MADCTL_MV 0x20
#define ST7789_Cmd_MADCTL_ML 0x10
#define ST7789_Cmd_MADCTL_RGB 0x00

#define ST77xx_MADCTL_MY 0x80
#define ST77xx_MADCTL_MX 0x40
#define ST77xx_MADCTL_MV 0x20
#define ST77xx_MADCTL_ML 0x10
#define ST77xx_MADCTL_BGR 0x08
#define ST77xx_MADCTL_MH 0x04

#define INITR_GREENTAB 0x00
#define INITR_REDTAB 0x01
#define INITR_BLACKTAB 0x02
#define INITR_18GREENTAB INITR_GREENTAB
#define INITR_18REDTAB INITR_REDTAB
#define INITR_18BLACKTAB INITR_BLACKTAB
#define INITR_144GREENTAB 0x01
#define INITR_MINI160x80 0x04
#define INITR_HALLOWING 0x05
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH 0x04
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_DISSET5 0xB6
#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5
#define ST7735_PWCTR6 0xFC
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1
#define ST77XX_NOP 0x00
#define ST77XX_SWRESET 0x01
#define ST77XX_RDDID 0x04
#define ST77XX_RDDST 0x09
#define ST77XX_SLPIN 0x10
#define ST77XX_SLPOUT 0x11
#define ST77XX_PTLON 0x12
#define ST77XX_NORON 0x13
#define ST77XX_INVOFF 0x20
#define ST77XX_INVON 0x21
#define ST77XX_DISPOFF 0x28
#define ST77XX_DISPON 0x29
#define ST77XX_CASET 0x2A
#define ST77XX_RASET 0x2B
#define ST77XX_RAMWR 0x2C
#define ST77XX_RAMRD 0x2E
#define ST77XX_PTLAR 0x30
#define ST77XX_TEOFF 0x34
#define ST77XX_TEON 0x35
#define ST77XX_MADCTL 0x36
#define ST77XX_COLMOD 0x3A
#define ST77XX_MADCTL_MY 0x80
#define ST77XX_MADCTL_MX 0x40
#define ST77XX_MADCTL_MV 0x20
#define ST77XX_MADCTL_ML 0x10
#define ST77XX_MADCTL_RGB 0x00
#define ST77XX_RDID1 0xDA
#define ST77XX_RDID2 0xDB
#define ST77XX_RDID3 0xDC
#define ST77XX_RDID4 0xDD
#define ST7735_SWRESET 0x01
#define ST7735_SLPOUT 0x11
#define ST7735_INVOFF 0x20
#define ST7735_COLMOD 0x3a
#define ST7735_MADCTL 0x36
#define ST7735_CASET 0x2a
#define ST7735_RASET 0x2b
#define ST7735_NORON 0x13
#define ST7735_DISPON 0x29
#define ST7735_DISPOFF 0x28
    
int ST7735_CURSOR_X;
int ST7735_CURSOR_Y;

void ST7735_Write(unsigned char data);
void ST7735_Command(unsigned char cmd);
void ST7735_Set_Window(int xs, int xe, int ys, int ye);
void ST7735_Set_Pixel(int x, int y, int color);
void ST7735_Write_8bits(unsigned char data);
void ST7735_Write_16bits(int data);
void ST7735_Draw_Image_16bits(const unsigned char *buffer, int x, int y, int w, int h);
void ST7735_Draw_Pixel_Image(const unsigned char *buffer, int x, int y, int w, int Pixels, int Color);
void ST7735_DrawRectangle(int x, int y, int width, int height, int color);
void ST7735_DrawRectangleA(int x, int y, int area, int color);
void ST7735_Fill(int color);
void ST7735_BgColor(int x, int y, int size_W, int size_H, int color);

void ST7735_Char(int dt, const unsigned long Font[], int color);
void ST7735_String_XY(const char *s, int x, int y, const unsigned long Font[], int Color);
void ST7735_String(const char *s, const unsigned long Font[], int Color);
void ST7735_Int_XY(long num, int x, int y, const unsigned long Font[], int color);
void ST7735_Int(long num, const unsigned long Font[], int color);
void ST7735_Float_XY(double f, long decimal, int x, int y, const unsigned long Font[], int color);
void ST7735_Float(double f, long decimal, const unsigned long Font[], int color);


void ST7735_Set_XY(int x, int y);
void ST7735_Init(void);

#endif	

