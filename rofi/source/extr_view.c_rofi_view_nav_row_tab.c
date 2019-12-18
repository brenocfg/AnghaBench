#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int filtered_lines; int quit; scalar_t__ prev_action; int /*<<< orphan*/  list_view; scalar_t__ selected_line; int /*<<< orphan*/  retv; scalar_t__* line_map; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_NEXT ; 
 int /*<<< orphan*/  MENU_OK ; 
 scalar_t__ ROW_TAB ; 
 int TRUE ; 
 size_t listview_get_selected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listview_nav_down (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rofi_view_nav_row_tab ( RofiViewState *state )
{
    if ( state->filtered_lines == 1 ) {
        state->retv              = MENU_OK;
        ( state->selected_line ) = state->line_map[listview_get_selected ( state->list_view )];
        state->quit              = 1;
        return;
    }

    // Double tab!
    if ( state->filtered_lines == 0 && ROW_TAB == state->prev_action ) {
        state->retv              = MENU_NEXT;
        ( state->selected_line ) = 0;
        state->quit              = TRUE;
    }
    else {
        listview_nav_down ( state->list_view );
    }
    state->prev_action = ROW_TAB;
}