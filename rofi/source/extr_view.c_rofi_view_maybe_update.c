#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ refilter; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  rofi_quit_main_loop () ; 
 int /*<<< orphan*/  rofi_view_finalize (TYPE_1__*) ; 
 TYPE_1__* rofi_view_get_active () ; 
 scalar_t__ rofi_view_get_completed (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_refilter (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_update (TYPE_1__*,int /*<<< orphan*/ ) ; 

void rofi_view_maybe_update ( RofiViewState *state )
{
    if ( rofi_view_get_completed ( state ) ) {
        // This menu is done.
        rofi_view_finalize ( state );
        // If there a state. (for example error) reload it.
        state = rofi_view_get_active ();

        // cleanup, if no more state to display.
        if ( state == NULL ) {
            // Quit main-loop.
            rofi_quit_main_loop ();
            return;
        }
    }

    // Update if requested.
    if ( state->refilter ) {
        rofi_view_refilter ( state );
    }
    rofi_view_update ( state, TRUE );
}