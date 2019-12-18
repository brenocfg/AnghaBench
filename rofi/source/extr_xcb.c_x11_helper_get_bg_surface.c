#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xcb_pixmap_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_4__ {int /*<<< orphan*/  height_in_pixels; int /*<<< orphan*/  width_in_pixels; } ;
struct TYPE_3__ {TYPE_2__* screen; int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 size_t ESETROOT_PMAP_ID ; 
 scalar_t__ XCB_NONE ; 
 int /*<<< orphan*/ * cairo_xcb_surface_create (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_root_pixmap (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * netatoms ; 
 int /*<<< orphan*/  root_visual ; 
 TYPE_1__* xcb ; 

cairo_surface_t * x11_helper_get_bg_surface ( void )
{
    xcb_pixmap_t pm = get_root_pixmap ( xcb->connection, xcb->screen, netatoms[ESETROOT_PMAP_ID] );
    if ( pm == XCB_NONE ) {
        return NULL;
    }
    return cairo_xcb_surface_create ( xcb->connection, pm, root_visual,
                                      xcb->screen->width_in_pixels, xcb->screen->height_in_pixels );
}