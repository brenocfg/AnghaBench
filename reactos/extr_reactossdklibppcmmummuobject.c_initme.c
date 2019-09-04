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
typedef  scalar_t__ MmuTrapHandler ;

/* Variables and functions */
 scalar_t__ HTABORG ; 
 int HTABSIZ ; 
 scalar_t__ TakeException ; 
 scalar_t__* callback ; 
 int /*<<< orphan*/  copy_trap_handler (int) ; 
 scalar_t__ fpenable ; 
 scalar_t__ ignore ; 

void initme()
{
    int i;

    for(i = 0; i < HTABSIZ / sizeof(int); i++)
    {
	((int *)HTABORG)[i] = 0;
    }

    /* Default to hang on unknown exception */
    for(i = 0; i < 30; i++)
    {
        callback[i] = (MmuTrapHandler)TakeException;
        if (i != 1) /* Preserve reset handler */
            copy_trap_handler(i);
    }

    /* Serial Interrupt */
    callback[5] = 0; /* Do nothing until the user asks */

    /* Program Exception */
    callback[6] = (MmuTrapHandler)TakeException;

    /* Floating point exception */
    callback[8] = fpenable;

    /* Ignore decrementer and EE */
    callback[9] = ignore;

    /* Single Step */
    callback[0x20] = (MmuTrapHandler)TakeException;
}