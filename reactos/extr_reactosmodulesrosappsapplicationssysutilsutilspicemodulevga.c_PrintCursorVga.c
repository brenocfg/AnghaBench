#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int ULONG ;
typedef  int UCHAR ;
struct TYPE_2__ {int usCurX; int y; int usCurY; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int GLOBAL_SCREEN_WIDTH ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 TYPE_1__* wWindow ; 

void PrintCursorVga(BOOLEAN bForce)
{
    static ULONG count=0;
    USHORT charoffset;
    UCHAR data;
    ULONG x=wWindow[OUTPUT_WINDOW].usCurX,y=wWindow[OUTPUT_WINDOW].y+wWindow[OUTPUT_WINDOW].usCurY;

	if( count++>250 )
	{
        count=0;

        charoffset = (y* GLOBAL_SCREEN_WIDTH + x);

		outb_p(0x0e,0x3d4);
		data=(UCHAR)((charoffset>>8)&0xFF);
		outb_p(data,0x3d5);

        outb_p(0x0f,0x3d4);
		data=(UCHAR)(charoffset & 0xFF);
		outb_p(data,0x3d5);
    }
}