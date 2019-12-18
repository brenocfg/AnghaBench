#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  filter; } ;
struct TYPE_10__ {char* name; } ;
struct TYPE_9__ {int /*<<< orphan*/  str; } ;
typedef  int /*<<< orphan*/  RofiViewState ;
typedef  size_t ModeMode ;
typedef  TYPE_1__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_MSG_MARKUP ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_8__ config ; 
 size_t curr_switcher ; 
 int /*<<< orphan*/  g_main_loop_quit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_append (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  g_string_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_string_new (char*) ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/  mode_init (TYPE_2__*) ; 
 TYPE_2__** modi ; 
 unsigned int num_modi ; 
 int /*<<< orphan*/  process_result ; 
 int /*<<< orphan*/ * rofi_view_create (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_view_error_dialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rofi_view_get_active () ; 
 int /*<<< orphan*/  rofi_view_set_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void run_switcher ( ModeMode mode )
{
    // Otherwise check if requested mode is enabled.
    for ( unsigned int i = 0; i < num_modi; i++ ) {
        if ( !mode_init ( modi[i] ) ) {
            GString *str = g_string_new ( "Failed to initialize the mode: " );
            g_string_append ( str, modi[i]->name );
            g_string_append ( str, "\n" );

            rofi_view_error_dialog ( str->str, ERROR_MSG_MARKUP );
            g_string_free ( str, FALSE );
            break;
        }
    }
    // Error dialog must have been created.
    if ( rofi_view_get_active () != NULL ) {
        return;
    }
    curr_switcher = mode;
    RofiViewState * state = rofi_view_create ( modi[mode], config.filter, 0, process_result );
    if ( state ) {
        rofi_view_set_active ( state );
    }
    if ( rofi_view_get_active () == NULL ) {
        g_main_loop_quit ( main_loop  );
    }
}