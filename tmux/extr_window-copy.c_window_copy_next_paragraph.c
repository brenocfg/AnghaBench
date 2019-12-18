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
struct screen {int dummy; } ;
struct window_copy_mode_data {scalar_t__ cy; scalar_t__ oy; int /*<<< orphan*/  backing; struct screen screen; } ;

/* Variables and functions */
 scalar_t__ screen_hsize (int /*<<< orphan*/ ) ; 
 scalar_t__ screen_size_y (struct screen*) ; 
 scalar_t__ window_copy_find_length (struct window_mode_entry*,scalar_t__) ; 
 int /*<<< orphan*/  window_copy_scroll_to (struct window_mode_entry*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
window_copy_next_paragraph(struct window_mode_entry *wme)
{
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = &data->screen;
	u_int				 maxy, ox, oy;

	oy = screen_hsize(data->backing) + data->cy - data->oy;
	maxy = screen_hsize(data->backing) + screen_size_y(s) - 1;

	while (oy < maxy && window_copy_find_length(wme, oy) == 0)
		oy++;

	while (oy < maxy && window_copy_find_length(wme, oy) > 0)
		oy++;

	ox = window_copy_find_length(wme, oy);
	window_copy_scroll_to(wme, ox, oy);
}