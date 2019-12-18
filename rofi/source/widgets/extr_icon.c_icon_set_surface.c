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
struct TYPE_4__ {int /*<<< orphan*/ * icon; scalar_t__ icon_fetch_id; } ;
typedef  TYPE_1__ icon ;
typedef  int /*<<< orphan*/  cairo_surface_t ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_surface_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ ) ; 

void icon_set_surface ( icon *icon, cairo_surface_t *surf )
{
    icon->icon_fetch_id = 0;
    if ( icon->icon ) {
        cairo_surface_destroy ( icon->icon );
        icon->icon = NULL;
    }
    if ( surf ) {
        cairo_surface_reference ( surf );
        icon->icon = surf;
    }
    widget_queue_redraw ( WIDGET ( icon ) );
}