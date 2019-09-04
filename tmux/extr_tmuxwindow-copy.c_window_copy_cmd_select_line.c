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
typedef  int u_int ;
struct window_mode_entry {int prefix; struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {scalar_t__ rectflag; int /*<<< orphan*/  lineflag; } ;
struct window_copy_cmd_state {struct window_mode_entry* wme; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_SEL_LEFT_RIGHT ; 
 int WINDOW_COPY_CMD_REDRAW ; 
 int /*<<< orphan*/  window_copy_cursor_down (struct window_mode_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_copy_cursor_end_of_line (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_cursor_start_of_line (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_start_selection (struct window_mode_entry*) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_select_line(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	struct window_copy_mode_data	*data = wme->data;
	u_int				 np = wme->prefix;

	data->lineflag = LINE_SEL_LEFT_RIGHT;
	data->rectflag = 0;

	window_copy_cursor_start_of_line(wme);
	window_copy_start_selection(wme);
	for (; np > 1; np--)
		window_copy_cursor_down(wme, 0);
	window_copy_cursor_end_of_line(wme);

	return (WINDOW_COPY_CMD_REDRAW);
}