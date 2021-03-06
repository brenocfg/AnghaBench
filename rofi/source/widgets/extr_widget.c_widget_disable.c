#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* parent; scalar_t__ enabled; } ;
typedef  TYPE_1__ widget ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  widget_queue_redraw (TYPE_1__*) ; 
 int /*<<< orphan*/  widget_update (TYPE_1__*) ; 

void widget_disable ( widget *widget )
{
    if ( widget && widget->enabled ) {
        widget->enabled = FALSE;
        widget_update ( widget );
        widget_update ( widget->parent );
        widget_queue_redraw ( widget );
    }
}