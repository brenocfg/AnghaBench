#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widget_trigger_action_cb ;
struct TYPE_3__ {void* trigger_action_cb_data; int /*<<< orphan*/  trigger_action; } ;
typedef  TYPE_1__ widget ;

/* Variables and functions */

void widget_set_trigger_action_handler ( widget *wid, widget_trigger_action_cb cb, void * cb_data )
{
    if ( wid == NULL ) {
        return;
    }
    wid->trigger_action         = cb;
    wid->trigger_action_cb_data = cb_data;
}