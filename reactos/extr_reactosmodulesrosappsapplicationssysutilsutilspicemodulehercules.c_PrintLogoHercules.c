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
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/ * cLogo ; 
 scalar_t__ pScreenBufferHercules ; 

void PrintLogoHercules(BOOLEAN bShow)
{
    LONG x,y;
    PUCHAR p;

    p=(PUCHAR)pScreenBufferHercules;
    for(y=0;y<24;y++)
    {
        for(x=0;x<8;x++)
        {
    	    p[ ( 0x2000* (( y + 8 ) & 0x3) )+
	    	    ( 90* ( (y + 8 ) >> 2) )+
		        (81+x)] = cLogo[y*8+x];
        }
    }
}