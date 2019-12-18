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
typedef  scalar_t__ ULONG ;
struct TYPE_2__ {scalar_t__ cy; scalar_t__ y; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClrLine (scalar_t__) ; 
 int /*<<< orphan*/  Home (size_t) ; 
 TYPE_1__* wWindow ; 

void Clear(USHORT Window)
{
    ULONG j;

    for(j=0;j<wWindow[Window].cy;j++)
    {
		ClrLine(wWindow[Window].y+j);
    }

    Home(Window);
}