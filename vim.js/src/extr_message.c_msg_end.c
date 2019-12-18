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
 int CMDLINE ; 
 int FALSE ; 
 int State ; 
 int TRUE ; 
 int /*<<< orphan*/  exiting ; 
 scalar_t__ need_wait_return ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  wait_return (int) ; 

int
msg_end()
{
    /*
     * If the string is larger than the window,
     * or the ruler option is set and we run into it,
     * we have to redraw the window.
     * Do not do this if we are abandoning the file or editing the command line.
     */
    if (!exiting && need_wait_return && !(State & CMDLINE))
    {
	wait_return(FALSE);
	return FALSE;
    }
    out_flush();
    return TRUE;
}