#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listview ;
typedef  scalar_t__ gboolean ;
struct TYPE_2__ {void* skip_absorb; void* quit; int /*<<< orphan*/ * line_map; int /*<<< orphan*/  selected_line; int /*<<< orphan*/  retv; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_CUSTOM_ACTION ; 
 int /*<<< orphan*/  MENU_OK ; 
 void* TRUE ; 
 size_t listview_get_selected (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rofi_view_listview_mouse_activated_cb ( listview *lv, gboolean custom, void *udata )
{
    RofiViewState *state = (RofiViewState *) udata;
    state->retv = MENU_OK;
    if ( custom ) {
        state->retv |= MENU_CUSTOM_ACTION;
    }
    ( state->selected_line ) = state->line_map[listview_get_selected ( lv )];
    // Quit
    state->quit        = TRUE;
    state->skip_absorb = TRUE;
}