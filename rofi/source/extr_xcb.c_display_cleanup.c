#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ screen_nbr; int /*<<< orphan*/ * screen; int /*<<< orphan*/ * connection; int /*<<< orphan*/ * source; int /*<<< orphan*/  ewmh; int /*<<< orphan*/ * sndisplay; int /*<<< orphan*/ * sncontext; int /*<<< orphan*/  bindings_seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_water_xcb_source_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_bindings_seat_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_display_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_launchee_context_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x11_monitors_free () ; 
 TYPE_1__* xcb ; 
 int /*<<< orphan*/  xcb_aux_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_ewmh_connection_wipe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ *) ; 

void display_cleanup ( void )
{
    if ( xcb->connection == NULL ) {
        return;
    }

    g_debug ( "Cleaning up XCB and XKB" );

    nk_bindings_seat_free ( xcb->bindings_seat );
    if ( xcb->sncontext != NULL ) {
        sn_launchee_context_unref ( xcb->sncontext );
        xcb->sncontext = NULL;
    }
    if ( xcb->sndisplay != NULL ) {
        sn_display_unref ( xcb->sndisplay );
        xcb->sndisplay = NULL;
    }
    x11_monitors_free ();
    xcb_ewmh_connection_wipe ( &( xcb->ewmh ) );
    xcb_flush ( xcb->connection );
    xcb_aux_sync ( xcb->connection );
    g_water_xcb_source_free ( xcb->source );
    xcb->source     = NULL;
    xcb->connection = NULL;
    xcb->screen     = NULL;
    xcb->screen_nbr = 0;
}