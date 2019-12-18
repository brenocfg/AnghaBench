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
typedef  int /*<<< orphan*/  xcb_generic_event_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  vout_display_t ;

/* Variables and functions */
 int /*<<< orphan*/  ProcessEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ xcb_connection_has_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_poll_for_event (int /*<<< orphan*/ *) ; 

int vlc_xcb_Manage(vout_display_t *vd, xcb_connection_t *conn)
{
    xcb_generic_event_t *ev;

    while ((ev = xcb_poll_for_event (conn)) != NULL)
        ProcessEvent(vd, ev);

    if (xcb_connection_has_error (conn))
    {
        msg_Err (vd, "X server failure");
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}