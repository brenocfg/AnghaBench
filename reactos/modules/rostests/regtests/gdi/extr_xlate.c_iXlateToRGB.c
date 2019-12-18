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
COLORREF
iXlateToRGB(ULONG iFormat, ULONG ulColor)
{
    ULONG ulRed, ulGreen, ulBlue;
    
    switch (iFormat)
    {
        case BMF_1BPP:
            return ulColor ? 0xffffff : 0;

        case BMF_4BPP:
        case BMF_8BPP:
        case BMF_16BPP_555:
            ulRed = (ulColor & 0x7C00) >> 7;
            ulRed |= ulRed >> 5;
            ulGreen = (ulColor & 0x3E0) >> 2;
            ulGreen |= ulGreen >> 5;
            ulBlue = (ulColor & 0x1F) << 3;
            ulBlue |= ulBlue >> 5;
            return RGB(ulRed, ulGreen, ulBlue);

        case BMF_16BPP_565:
            ulRed = (ulColor & 0xF800) >> 8;
            ulRed |= ulRed >> 5;
            ulGreen = (ulColor & 0x7E0) >> 3;
            ulGreen |= ulGreen >> 6;
            ulBlue = (ulColor & 0x1F) << 3;
            ulBlue |= ulBlue >> 5;
            return RGB(ulRed, ulGreen, ulBlue);

        case BMF_24BPP_RGB:
        case BMF_32BPP_RGB:
            return ulColor;

        case BMF_24BPP_BGR:
        case BMF_32BPP_BGR:
            ulRed = GetRValue(ulColor);
            ulGreen = GetGValue(ulColor);
            ulBlue = GetBValue(ulColor);
            return RGB(ulBlue, ulGreen, ulRed);
    }
    return 0;
}