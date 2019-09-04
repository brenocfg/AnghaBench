#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ULONG ;
typedef  int COLORREF ;

/* Variables and functions */
#define  BMF_16BPP_555 136 
#define  BMF_16BPP_565 135 
#define  BMF_1BPP 134 
#define  BMF_24BPP_BGR 133 
#define  BMF_24BPP_RGB 132 
#define  BMF_32BPP_BGR 131 
#define  BMF_32BPP_RGB 130 
#define  BMF_4BPP 129 
#define  BMF_8BPP 128 
 int GetBValue (int) ; 
 int GetGValue (int) ; 
 int GetRValue (int) ; 
 int RGB (int,int,int) ; 

__attribute__((used)) static
ULONG
iXlateFromRGB(ULONG iFormat, COLORREF crColor)
{
    ULONG ulRed, ulGreen, ulBlue;
    
    ulRed = GetRValue(crColor);
    ulGreen = GetGValue(crColor);
    ulBlue = GetBValue(crColor);

    switch (iFormat)
    {
        case BMF_1BPP:
            return crColor ? 0xffffff : 0;

        case BMF_4BPP:
        case BMF_8BPP:
        case BMF_16BPP_555:
            ulRed = (ulRed & 0xF8) >> 3;
            ulGreen = (ulGreen & 0xF8) >> 3;
            ulBlue = (ulBlue & 0xF8) >> 3;
            return ulRed << 10 | ulGreen << 5 | ulBlue;

        case BMF_16BPP_565:
            ulRed = (ulRed & 0xF8) >> 3;
            ulGreen = (ulGreen & 0xFC) >> 2;
            ulBlue = (ulBlue & 0xF8) >> 3;
            return ulRed << 11 | ulGreen << 5 | ulBlue;

        case BMF_24BPP_RGB:
        case BMF_32BPP_RGB:
            return crColor;

        case BMF_24BPP_BGR:
        case BMF_32BPP_BGR:
            return RGB(ulBlue, ulGreen, ulRed);
    }
    return 0;
}