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
typedef  int /*<<< orphan*/  RofiViewState ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  dmenu_mode ; 
 int /*<<< orphan*/  mode_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_set_return_code (int) ; 
 int /*<<< orphan*/  rofi_view_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_view_set_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dmenu_finish ( RofiViewState *state, int retv )
{
    if ( retv == FALSE ) {
        rofi_set_return_code ( EXIT_FAILURE );
    }
    else if ( retv >= 10 ) {
        rofi_set_return_code ( retv );
    }
    else{
        rofi_set_return_code ( EXIT_SUCCESS );
    }
    rofi_view_set_active ( NULL );
    rofi_view_free ( state );
    mode_destroy ( &dmenu_mode );
}