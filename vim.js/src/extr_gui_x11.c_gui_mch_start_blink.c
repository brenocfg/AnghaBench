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
typedef  scalar_t__ XtIntervalId ;
struct TYPE_2__ {scalar_t__ in_focus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLINK_ON ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XtAppAddTimeOut (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XtRemoveTimeOut (scalar_t__) ; 
 int /*<<< orphan*/  app_context ; 
 scalar_t__ blink_offtime ; 
 scalar_t__ blink_ontime ; 
 int /*<<< orphan*/  blink_state ; 
 scalar_t__ blink_timer ; 
 scalar_t__ blink_waittime ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_update_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_x11_blink_cb ; 

void
gui_mch_start_blink()
{
    if (blink_timer != (XtIntervalId)0)
	XtRemoveTimeOut(blink_timer);
    /* Only switch blinking on if none of the times is zero */
    if (blink_waittime && blink_ontime && blink_offtime && gui.in_focus)
    {
	blink_timer = XtAppAddTimeOut(app_context, blink_waittime,
						      gui_x11_blink_cb, NULL);
	blink_state = BLINK_ON;
	gui_update_cursor(TRUE, FALSE);
    }
}