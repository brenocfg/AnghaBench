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
typedef  int USHORT ;
typedef  size_t ULONG ;
typedef  int* PUSHORT ;

/* Variables and functions */
 size_t GLOBAL_SCREEN_HEIGHT ; 
 size_t GLOBAL_SCREEN_WIDTH ; 
 int /*<<< orphan*/  pScreenBufferVga ; 

void InvertLineVga(ULONG line)
{
    ULONG i;
    PUSHORT p = (PUSHORT)pScreenBufferVga;
    USHORT attr;

    if(line < GLOBAL_SCREEN_HEIGHT)
    {
        attr = p[line*GLOBAL_SCREEN_WIDTH]>>8;
        attr = ((attr & 0x07)<<4) | ((attr & 0xF0)>>4);
        attr <<= 8;
        for(i=0;i<GLOBAL_SCREEN_WIDTH;i++)
            p[line*GLOBAL_SCREEN_WIDTH + i] = (p[line*GLOBAL_SCREEN_WIDTH + i] & 0x00FF) | attr;
    }
}