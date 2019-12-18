#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  widget ;
struct TYPE_6__ {int /*<<< orphan*/  get_desired_height; int /*<<< orphan*/  find_mouse_target; int /*<<< orphan*/  update; int /*<<< orphan*/  resize; int /*<<< orphan*/  free; int /*<<< orphan*/  draw; } ;
struct TYPE_7__ {TYPE_1__ widget; } ;
typedef  TYPE_2__ container ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  WIDGET_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  container_draw ; 
 int /*<<< orphan*/  container_find_mouse_target ; 
 int /*<<< orphan*/  container_free ; 
 int /*<<< orphan*/  container_get_desired_height ; 
 int /*<<< orphan*/  container_resize ; 
 int /*<<< orphan*/  container_update ; 
 TYPE_2__* g_malloc0 (int) ; 
 int /*<<< orphan*/  widget_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

container * container_create ( widget *parent, const char *name )
{
    container *b = g_malloc0 ( sizeof ( container ) );
    // Initialize widget.
    widget_init ( WIDGET ( b ), parent, WIDGET_TYPE_UNKNOWN, name );
    b->widget.draw               = container_draw;
    b->widget.free               = container_free;
    b->widget.resize             = container_resize;
    b->widget.update             = container_update;
    b->widget.find_mouse_target  = container_find_mouse_target;
    b->widget.get_desired_height = container_get_desired_height;
    return b;
}