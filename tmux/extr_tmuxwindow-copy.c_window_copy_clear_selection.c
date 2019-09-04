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
struct window_copy_mode_data {scalar_t__ cy; scalar_t__ oy; scalar_t__ cx; int /*<<< orphan*/  backing; int /*<<< orphan*/  lineflag; int /*<<< orphan*/  cursordrag; int /*<<< orphan*/  screen; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSORDRAG_NONE ; 
 int /*<<< orphan*/  LINE_SEL_NONE ; 
 int /*<<< orphan*/  screen_clear_selection (int /*<<< orphan*/ *) ; 
 scalar_t__ screen_hsize (int /*<<< orphan*/ ) ; 
 scalar_t__ window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 int /*<<< orphan*/  window_copy_update_cursor (struct window_mode_entry*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
window_copy_clear_selection(struct window_mode_entry *wme)
{
	struct window_copy_mode_data   *data = wme->data;
	u_int				px, py;

	screen_clear_selection(&data->screen);

	data->cursordrag = CURSORDRAG_NONE;
	data->lineflag = LINE_SEL_NONE;

	py = screen_hsize(data->backing) + data->cy - data->oy;
	px = window_copy_find_length(wme, py);
	if (data->cx > px)
		window_copy_update_cursor(wme, px, data->cy);
}