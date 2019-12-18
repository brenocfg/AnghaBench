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
struct TYPE_3__ {unsigned int selected_line; unsigned int num_lines; unsigned int* line_map; int /*<<< orphan*/  list_view; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 unsigned int listview_get_selected (int /*<<< orphan*/ ) ; 

unsigned int rofi_view_get_next_position ( const RofiViewState *state )
{
    unsigned int next_pos = state->selected_line;
    unsigned int selected = listview_get_selected ( state->list_view );
    if ( ( selected + 1 ) < state->num_lines ) {
        ( next_pos ) = state->line_map[selected + 1];
    }
    return next_pos;
}