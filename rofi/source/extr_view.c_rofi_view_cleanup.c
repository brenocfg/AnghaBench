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
struct TYPE_4__ {scalar_t__ idle_timeout; scalar_t__ repaint_source; scalar_t__ main_window; int /*<<< orphan*/  views; int /*<<< orphan*/  edit_pixmap; int /*<<< orphan*/  gc; int /*<<< orphan*/ * edit_surf; int /*<<< orphan*/ * edit_draw; int /*<<< orphan*/ * fake_bg; } ;
struct TYPE_3__ {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 TYPE_2__ CacheState ; 
 scalar_t__ XCB_COLORMAP_NONE ; 
 scalar_t__ XCB_WINDOW_NONE ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_queue_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_source_remove (scalar_t__) ; 
 scalar_t__ map ; 
 TYPE_1__* xcb ; 
 int /*<<< orphan*/  xcb_destroy_window (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_free_colormap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xcb_free_gc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_free_pixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_unmap_window (int /*<<< orphan*/ ,scalar_t__) ; 

void rofi_view_cleanup ()
{
    g_debug ( "Cleanup." );
    if ( CacheState.idle_timeout > 0 ) {
        g_source_remove ( CacheState.idle_timeout );
        CacheState.idle_timeout = 0;
    }
    if ( CacheState.repaint_source > 0 ) {
        g_source_remove ( CacheState.repaint_source );
        CacheState.repaint_source = 0;
    }
    if ( CacheState.fake_bg ) {
        cairo_surface_destroy ( CacheState.fake_bg );
        CacheState.fake_bg = NULL;
    }
    if ( CacheState.edit_draw ) {
        cairo_destroy ( CacheState.edit_draw );
        CacheState.edit_draw = NULL;
    }
    if ( CacheState.edit_surf ) {
        cairo_surface_destroy ( CacheState.edit_surf );
        CacheState.edit_surf = NULL;
    }
    if ( CacheState.main_window != XCB_WINDOW_NONE ) {
        g_debug ( "Unmapping and free'ing window" );
        xcb_unmap_window ( xcb->connection, CacheState.main_window );
        xcb_free_gc ( xcb->connection, CacheState.gc );
        xcb_free_pixmap ( xcb->connection, CacheState.edit_pixmap );
        xcb_destroy_window ( xcb->connection, CacheState.main_window );
        CacheState.main_window = XCB_WINDOW_NONE;
    }
    if ( map != XCB_COLORMAP_NONE ) {
        xcb_free_colormap ( xcb->connection, map );
        map = XCB_COLORMAP_NONE;
    }
    xcb_flush ( xcb->connection );
    g_assert ( g_queue_is_empty ( &( CacheState.views ) ) );
}