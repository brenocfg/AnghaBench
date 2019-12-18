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
typedef  scalar_t__ u_int ;
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {scalar_t__ cy; scalar_t__ oy; scalar_t__ lineflag; scalar_t__ endsely; int /*<<< orphan*/  cx; int /*<<< orphan*/  screen; int /*<<< orphan*/  backing; } ;
struct window_copy_cmd_state {struct window_mode_entry* wme; } ;
typedef  enum window_copy_cmd_action { ____Placeholder_window_copy_cmd_action } window_copy_cmd_action ;

/* Variables and functions */
 scalar_t__ LINE_SEL_RIGHT_LEFT ; 
 int WINDOW_COPY_CMD_REDRAW ; 
 scalar_t__ screen_hsize (int /*<<< orphan*/ ) ; 
 scalar_t__ screen_size_y (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 int /*<<< orphan*/  window_copy_other_end (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_update_selection (struct window_mode_entry*,int) ; 

__attribute__((used)) static enum window_copy_cmd_action
window_copy_cmd_history_bottom(struct window_copy_cmd_state *cs)
{
	struct window_mode_entry	*wme = cs->wme;
	struct window_copy_mode_data	*data = wme->data;
	u_int				 oy;

	oy = screen_hsize(data->backing) + data->cy - data->oy;
	if (data->lineflag == LINE_SEL_RIGHT_LEFT && oy == data->endsely)
		window_copy_other_end(wme);

	data->cy = screen_size_y(&data->screen) - 1;
	data->cx = window_copy_find_length(wme, data->cy);
	data->oy = 0;

	window_copy_update_selection(wme, 1);
	return (WINDOW_COPY_CMD_REDRAW);
}