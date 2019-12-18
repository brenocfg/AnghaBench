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
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ g_fCBrkPressed ; 
 scalar_t__ g_fCtrlCPressed ; 
 int /*<<< orphan*/  got_int ; 

void
mch_breakcheck(void)
{
#ifndef FEAT_GUI_W32	    /* never used */
    if (g_fCtrlCPressed || g_fCBrkPressed)
    {
	g_fCtrlCPressed = g_fCBrkPressed = FALSE;
	got_int = TRUE;
    }
#endif
}