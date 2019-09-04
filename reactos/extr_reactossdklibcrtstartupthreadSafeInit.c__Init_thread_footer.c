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
 int /*<<< orphan*/  _Init_global_epoch ; 
 int _InterlockedIncrement (int /*<<< orphan*/ *) ; 

void
_Init_thread_footer(volatile int* ptss)
{
    /* Initialization is complete */
    *ptss = _InterlockedIncrement(&_Init_global_epoch);
}