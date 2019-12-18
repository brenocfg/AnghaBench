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

/* Variables and functions */
 int /*<<< orphan*/  GetKeyData () ; 
 int GetKeyStatus () ; 
 int /*<<< orphan*/  KeStallExecutionProcessor (int) ; 
 int OUTPUT_BUFFER_FULL ; 

void KeyboardFlushKeyboardQueue(void)
{
	//__udelay(10);
	KeStallExecutionProcessor(10);
    while(GetKeyStatus()&OUTPUT_BUFFER_FULL)
    {
        GetKeyData();
		//__udelay(10);
		KeStallExecutionProcessor(10);
    }
}