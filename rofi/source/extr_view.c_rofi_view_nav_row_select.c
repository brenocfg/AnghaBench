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
struct TYPE_3__ {unsigned int filtered_lines; int /*<<< orphan*/  refilter; int /*<<< orphan*/  text; int /*<<< orphan*/ * line_map; int /*<<< orphan*/  sw; int /*<<< orphan*/ * list_view; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  MOVE_END ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 unsigned int listview_get_selected (int /*<<< orphan*/ *) ; 
 char* mode_get_completion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textbox_keybinding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textbox_text (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) inline static void rofi_view_nav_row_select ( RofiViewState *state )
{
    if ( state->list_view == NULL ) {
        return;
    }
    unsigned int selected = listview_get_selected ( state->list_view );
    // If a valid item is selected, return that..
    if ( selected < state->filtered_lines ) {
        char *str = mode_get_completion ( state->sw, state->line_map[selected] );
        textbox_text ( state->text, str );
        g_free ( str );
        textbox_keybinding ( state->text, MOVE_END );
        state->refilter = TRUE;
    }
}