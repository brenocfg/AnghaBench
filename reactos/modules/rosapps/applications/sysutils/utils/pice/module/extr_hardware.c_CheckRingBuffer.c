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
struct TYPE_2__ {scalar_t__ cy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Acquire_Output_Lock () ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PrintRingBuffer (scalar_t__) ; 
 int /*<<< orphan*/  Release_Output_Lock () ; 
 scalar_t__ ulInPos ; 
 scalar_t__ ulOldInPos ; 
 TYPE_1__* wWindow ; 

void CheckRingBuffer(void)
{
//    ENTER_FUNC();

    Acquire_Output_Lock();

	if(ulInPos != ulOldInPos )
	{
		ulOldInPos = ulInPos;
		PrintRingBuffer(wWindow[OUTPUT_WINDOW].cy-1);
	}

    Release_Output_Lock();

//    LEAVE_FUNC();
}