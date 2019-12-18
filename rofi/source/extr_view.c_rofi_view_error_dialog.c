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
typedef  int /*<<< orphan*/  box ;
struct TYPE_11__ {int flags; int /*<<< orphan*/  main_window; } ;
struct TYPE_10__ {int /*<<< orphan*/ * sncontext; int /*<<< orphan*/  connection; } ;
struct TYPE_9__ {int /*<<< orphan*/ * main_window; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  list_view; int /*<<< orphan*/ * text; int /*<<< orphan*/  finalize; int /*<<< orphan*/  menu_flags; int /*<<< orphan*/  retv; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 TYPE_8__ CacheState ; 
 int /*<<< orphan*/  MENU_CANCEL ; 
 int /*<<< orphan*/  MENU_ERROR_DIALOG ; 
 int MENU_NORMAL_WINDOW ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  ROFI_ORIENTATION_VERTICAL ; 
 int TB_AUTOHEIGHT ; 
 int TB_MARKUP ; 
 int TB_WRAP ; 
 int TRUE ; 
 int /*<<< orphan*/ * WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WIDGET_TYPE_TEXTBOX_TEXT ; 
 TYPE_1__* __rofi_view_state_create () ; 
 int /*<<< orphan*/  box_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* box_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_set_fixed_num_lines (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_result ; 
 int /*<<< orphan*/  rofi_view_calculate_window_position (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_calculate_window_width (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_set_active (TYPE_1__*) ; 
 int /*<<< orphan*/  rofi_view_window_update_size (TYPE_1__*) ; 
 int /*<<< orphan*/  sn_launchee_context_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * textbox_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  widget_get_desired_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  widget_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* xcb ; 
 int /*<<< orphan*/  xcb_map_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rofi_view_error_dialog ( const char *msg, int markup )
{
    RofiViewState *state = __rofi_view_state_create ();
    state->retv       = MENU_CANCEL;
    state->menu_flags = MENU_ERROR_DIALOG;
    state->finalize   = process_result;

    state->main_window = box_create ( NULL, "window", ROFI_ORIENTATION_VERTICAL );
    box *box = box_create ( WIDGET ( state->main_window ), "error-message", ROFI_ORIENTATION_VERTICAL );
    box_add ( state->main_window, WIDGET ( box ), TRUE );
    state->text = textbox_create ( WIDGET ( box ), WIDGET_TYPE_TEXTBOX_TEXT, "textbox", ( TB_AUTOHEIGHT | TB_WRAP ) + ( ( markup ) ? TB_MARKUP : 0 ),
                                   NORMAL, ( msg != NULL ) ? msg : "", 0, 0 );
    box_add ( box, WIDGET ( state->text ), TRUE );

    // Make sure we enable fixed num lines when in normal window mode.
    if ( ( CacheState.flags & MENU_NORMAL_WINDOW ) == MENU_NORMAL_WINDOW ) {
        listview_set_fixed_num_lines ( state->list_view );
    }
    rofi_view_calculate_window_width ( state );
    // Need to resize otherwise calculated desired height is wrong.
    widget_resize ( WIDGET ( state->main_window ), state->width, 100 );
    // resize window vertically to suit
    state->height = widget_get_desired_height ( WIDGET ( state->main_window ) );

    // Calculte window position.
    rofi_view_calculate_window_position ( state );

    // Move the window to the correct x,y position.
    rofi_view_window_update_size ( state );

    // Display it.
    xcb_map_window ( xcb->connection, CacheState.main_window );
    widget_queue_redraw ( WIDGET ( state->main_window ) );

    if ( xcb->sncontext != NULL ) {
        sn_launchee_context_complete ( xcb->sncontext );
    }

    // Set it as current window.
    rofi_view_set_active ( state );
    return TRUE;
}