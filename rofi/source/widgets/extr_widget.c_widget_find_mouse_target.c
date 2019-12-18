#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; TYPE_1__* (* find_mouse_target ) (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ widget ;
typedef  int /*<<< orphan*/  gint ;
typedef  scalar_t__ WidgetType ;

/* Variables and functions */
 TYPE_1__* stub1 (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

widget *widget_find_mouse_target ( widget *wid, WidgetType type, gint x, gint y )
{
    if ( !wid ) {
        return NULL;
    }

    if ( wid->find_mouse_target ) {
        widget *target = wid->find_mouse_target ( wid, type, x, y );
        if ( target != NULL ) {
            return target;
        }
    }
    if ( wid->type == type ) {
        return wid;
    }
    return NULL;
}