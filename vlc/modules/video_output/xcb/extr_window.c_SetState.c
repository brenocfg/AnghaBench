#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_window_t ;
struct TYPE_6__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  wm_state_below; int /*<<< orphan*/  wm_state_above; } ;
typedef  TYPE_2__ vout_window_sys_t ;

/* Variables and functions */
 unsigned int VOUT_WINDOW_STATE_ABOVE ; 
 unsigned int VOUT_WINDOW_STATE_BELOW ; 
 int /*<<< orphan*/  change_wm_state (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SetState(vout_window_t *wnd, unsigned state)
{
    vout_window_sys_t *sys = wnd->sys;
    bool above = (state & VOUT_WINDOW_STATE_ABOVE) != 0;
    bool below = (state & VOUT_WINDOW_STATE_BELOW) != 0;

    change_wm_state(wnd, above, sys->wm_state_above);
    change_wm_state(wnd, below, sys->wm_state_below);
    xcb_flush(sys->conn);
}