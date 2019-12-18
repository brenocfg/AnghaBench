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
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {int /*<<< orphan*/  screen; } ;

/* Variables and functions */
 int /*<<< orphan*/  screen_size_y (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_copy_redraw_lines (struct window_mode_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
window_copy_redraw_screen(struct window_mode_entry *wme)
{
	struct window_copy_mode_data	*data = wme->data;

	window_copy_redraw_lines(wme, 0, screen_size_y(&data->screen));
}