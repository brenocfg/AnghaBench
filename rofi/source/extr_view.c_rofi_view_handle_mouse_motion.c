#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* gint ;
struct TYPE_4__ {int /*<<< orphan*/ * motion_target; void* y; void* x; } ;
struct TYPE_5__ {TYPE_1__ mouse; } ;
typedef  TYPE_2__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  widget_motion_notify (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  widget_xy_to_relative (int /*<<< orphan*/ *,void**,void**) ; 

void rofi_view_handle_mouse_motion ( RofiViewState *state, gint x, gint y )
{
    state->mouse.x = x;
    state->mouse.y = y;
    if ( state->mouse.motion_target != NULL ) {
        widget_xy_to_relative ( state->mouse.motion_target, &x, &y );
        widget_motion_notify ( state->mouse.motion_target, x, y );
    }
}