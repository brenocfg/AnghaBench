#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/  edit_surf; int /*<<< orphan*/  edit_draw; int /*<<< orphan*/  edit_pixmap; int /*<<< orphan*/  main_window; } ;
struct TYPE_8__ {int /*<<< orphan*/  depth; } ;
struct TYPE_7__ {int /*<<< orphan*/  connection; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  main_window; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 TYPE_5__ CacheState ; 
 int /*<<< orphan*/  WIDGET (int /*<<< orphan*/ ) ; 
 int XCB_CONFIG_WINDOW_HEIGHT ; 
 int XCB_CONFIG_WINDOW_WIDTH ; 
 int XCB_CONFIG_WINDOW_X ; 
 int XCB_CONFIG_WINDOW_Y ; 
 int /*<<< orphan*/  cairo_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_xcb_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* depth ; 
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visual ; 
 int /*<<< orphan*/  widget_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* xcb ; 
 int /*<<< orphan*/  xcb_configure_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_create_pixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_free_pixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_generate_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rofi_view_window_update_size ( RofiViewState * state )
{
    uint16_t mask   = XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT;
    uint32_t vals[] = { state->x, state->y, state->width, state->height };

    // Display it.
    xcb_configure_window ( xcb->connection, CacheState.main_window, mask, vals );
    cairo_destroy ( CacheState.edit_draw );
    cairo_surface_destroy ( CacheState.edit_surf );

    xcb_free_pixmap ( xcb->connection, CacheState.edit_pixmap );
    CacheState.edit_pixmap = xcb_generate_id ( xcb->connection );
    xcb_create_pixmap ( xcb->connection, depth->depth,
                        CacheState.edit_pixmap, CacheState.main_window, state->width, state->height );

    CacheState.edit_surf = cairo_xcb_surface_create ( xcb->connection, CacheState.edit_pixmap, visual, state->width, state->height );
    CacheState.edit_draw = cairo_create ( CacheState.edit_surf );

    g_debug ( "Re-size window based internal request: %dx%d.", state->width, state->height );
    // Should wrap main window in a widget.
    widget_resize ( WIDGET ( state->main_window ), state->width, state->height );
}