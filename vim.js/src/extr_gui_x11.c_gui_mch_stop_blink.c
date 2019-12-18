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
typedef  scalar_t__ XtIntervalId ;

/* Variables and functions */
 scalar_t__ BLINK_NONE ; 
 scalar_t__ BLINK_OFF ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XtRemoveTimeOut (scalar_t__) ; 
 scalar_t__ blink_state ; 
 scalar_t__ blink_timer ; 
 int /*<<< orphan*/  gui_update_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gui_mch_stop_blink()
{
    if (blink_timer != (XtIntervalId)0)
    {
	XtRemoveTimeOut(blink_timer);
	blink_timer = (XtIntervalId)0;
    }
    if (blink_state == BLINK_OFF)
	gui_update_cursor(TRUE, FALSE);
    blink_state = BLINK_NONE;
}