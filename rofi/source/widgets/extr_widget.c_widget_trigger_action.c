#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  trigger_action_cb_data; int /*<<< orphan*/  (* trigger_action ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ widget ;
typedef  int /*<<< orphan*/  guint ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  WidgetTriggerActionResult ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

WidgetTriggerActionResult widget_trigger_action ( widget *wid, guint action, gint x, gint y )
{
    if ( wid && wid->trigger_action ) {
        return wid->trigger_action ( wid, action, x, y, wid->trigger_action_cb_data );
    }
    return FALSE;
}