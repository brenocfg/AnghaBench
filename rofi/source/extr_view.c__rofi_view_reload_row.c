#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  num_lines; int /*<<< orphan*/  list_view; void* distance; void* line_map; int /*<<< orphan*/  sw; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (void*) ; 
 void* g_malloc0_n (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  listview_set_max_lines (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_get_num_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rofi_view_reload_message_bar (TYPE_1__*) ; 

__attribute__((used)) static void _rofi_view_reload_row ( RofiViewState *state )
{
    g_free ( state->line_map );
    g_free ( state->distance );
    state->num_lines = mode_get_num_entries ( state->sw );
    state->line_map  = g_malloc0_n ( state->num_lines, sizeof ( unsigned int ) );
    state->distance  = g_malloc0_n ( state->num_lines, sizeof ( int ) );
    listview_set_max_lines ( state->list_view, state->num_lines );
    rofi_view_reload_message_bar ( state );
}