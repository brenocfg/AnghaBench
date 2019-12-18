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
typedef  size_t USHORT ;
struct TYPE_2__ {size_t cy; size_t y; int /*<<< orphan*/  bScrollDisabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClrLine (size_t) ; 
 int /*<<< orphan*/  CopyLineTo (size_t,size_t) ; 
 TYPE_1__* wWindow ; 

void ScrollUp(USHORT Window)
{
    USHORT i;

    return;

	if(!wWindow[Window].bScrollDisabled)
	{
		for(i=1;i<wWindow[Window].cy;i++)
		{
			CopyLineTo((USHORT)(wWindow[Window].y+i-1),(USHORT)(wWindow[Window].y+i));
		}
		ClrLine((USHORT)(wWindow[Window].y+wWindow[Window].cy-1));
	}
}