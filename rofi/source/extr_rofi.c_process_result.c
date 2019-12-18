#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * sw; } ;
typedef  TYPE_1__ RofiViewState ;
typedef  int ModeMode ;
typedef  int /*<<< orphan*/  Mode ;
typedef  int /*<<< orphan*/  MenuReturn ;

/* Variables and functions */
 int MODE_EXIT ; 
 int NEXT_DIALOG ; 
 int PREVIOUS_DIALOG ; 
 int RELOAD_DIALOG ; 
 int RESET_DIALOG ; 
 int curr_switcher ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 int mode_result (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,unsigned int) ; 
 int /*<<< orphan*/ * modi ; 
 int num_modi ; 
 int /*<<< orphan*/  rofi_view_clear_input (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_free (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_get_return_value (TYPE_1__*) ; 
 unsigned int rofi_view_get_selected_line (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_get_user_input (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_set_active (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_switch_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 

void process_result ( RofiViewState *state )
{
    Mode *sw = state->sw;
    rofi_view_set_active ( NULL );
    if ( sw != NULL ) {
        unsigned int selected_line = rofi_view_get_selected_line ( state );;
        MenuReturn   mretv         = rofi_view_get_return_value ( state );
        char         *input        = g_strdup ( rofi_view_get_user_input ( state ) );
        ModeMode     retv          = mode_result ( sw, mretv, &input, selected_line );
        g_free ( input );

        ModeMode mode = curr_switcher;
        // Find next enabled
        if ( retv == NEXT_DIALOG ) {
            mode = ( mode + 1 ) % num_modi;
        }
        else if ( retv == PREVIOUS_DIALOG ) {
            if ( mode == 0 ) {
                mode = num_modi - 1;
            }
            else {
                mode = ( mode - 1 ) % num_modi;
            }
        }
        else if ( retv == RELOAD_DIALOG ) {
            // do nothing.
        }
        else if ( retv == RESET_DIALOG ) {
            rofi_view_clear_input ( state );
        }
        else if ( retv < MODE_EXIT ) {
            mode = ( retv ) % num_modi;
        }
        else {
            mode = retv;
        }
        if ( mode != MODE_EXIT ) {
            /**
             * Load in the new mode.
             */
            rofi_view_switch_mode ( state, modi[mode] );
            rofi_view_set_active ( state );
            curr_switcher = mode;
            return;
        }
    }
    rofi_view_free ( state );
}