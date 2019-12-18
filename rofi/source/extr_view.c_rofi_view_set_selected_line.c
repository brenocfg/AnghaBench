#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  main_window; } ;
struct TYPE_6__ {int /*<<< orphan*/  connection; } ;
struct TYPE_5__ {unsigned int selected_line; unsigned int filtered_lines; unsigned int* line_map; int /*<<< orphan*/  list_view; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 TYPE_4__ CacheState ; 
 unsigned int UINT32_MAX ; 
 int /*<<< orphan*/  listview_set_selected (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* xcb ; 
 int /*<<< orphan*/  xcb_clear_area (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 

void rofi_view_set_selected_line ( RofiViewState *state, unsigned int selected_line )
{
    state->selected_line = selected_line;
    // Find the line.
    unsigned int selected = 0;
    for ( unsigned int i = 0; ( ( state->selected_line ) ) < UINT32_MAX && !selected && i < state->filtered_lines; i++ ) {
        if ( state->line_map[i] == ( state->selected_line ) ) {
            selected = i;
            break;
        }
    }
    listview_set_selected ( state->list_view, selected );
    xcb_clear_area ( xcb->connection, CacheState.main_window, 1, 0, 0, 1, 1 );
    xcb_flush ( xcb->connection );
}