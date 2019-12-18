#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ find_arg (char*) ; 
 int /*<<< orphan*/  g_timeout_add (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_warning (char*,int) ; 
 int /*<<< orphan*/  lazy_grab_keyboard ; 
 int /*<<< orphan*/  lazy_grab_pointer ; 
 int /*<<< orphan*/  take_keyboard (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  take_pointer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  x11_create_visual_and_colormap () ; 
 int /*<<< orphan*/  xcb_stuff_get_root_window () ; 

gboolean display_late_setup ( void )
{
    x11_create_visual_and_colormap ();

    /**
     * Create window (without showing)
     */
    // Try to grab the keyboard as early as possible.
    // We grab this using the rootwindow (as dmenu does it).
    // this seems to result in the smallest delay for most people.
    if ( find_arg ( "-normal-window" ) >= 0 ) {
        return TRUE;
    }
    if ( find_arg ( "-no-lazy-grab" ) >= 0 ) {
        if ( !take_keyboard ( xcb_stuff_get_root_window (), 500 ) ) {
            g_warning ( "Failed to grab keyboard, even after %d uS.", 500 * 1000 );
            return FALSE;
        }
        if ( !take_pointer ( xcb_stuff_get_root_window (), 100 ) ) {
            g_warning ( "Failed to grab mouse pointer, even after %d uS.", 100 * 1000 );
        }
    }
    else {
        if ( !take_keyboard ( xcb_stuff_get_root_window (), 0 ) ) {
            g_timeout_add ( 1, lazy_grab_keyboard, NULL );
        }
        if ( !take_pointer ( xcb_stuff_get_root_window (), 0 ) ) {
            g_timeout_add ( 1, lazy_grab_pointer, NULL );
        }
    }
    return TRUE;
}