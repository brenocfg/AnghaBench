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
typedef  int /*<<< orphan*/  widget ;
typedef  int /*<<< orphan*/  gint ;
struct TYPE_4__ {TYPE_2__* child; } ;
typedef  TYPE_1__ container ;
typedef  int /*<<< orphan*/  WidgetType ;
struct TYPE_5__ {scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/ * widget_find_mouse_target (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_intersect (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static widget *container_find_mouse_target ( widget *wid, WidgetType type, gint x, gint y )
{
    container *b = (container *) wid;
    if ( !widget_intersect ( b->child, x, y ) ) {
        return NULL;
    }

    x -= b->child->x;
    y -= b->child->y;
    return widget_find_mouse_target ( b->child, type, x, y );
}