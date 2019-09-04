#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {struct screen* backing; } ;
struct screen {int /*<<< orphan*/  grid; } ;
struct TYPE_3__ {int size; char* data; } ;
struct grid_cell {TYPE_1__ data; } ;
struct TYPE_4__ {scalar_t__ cellsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_get_cell (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct grid_cell*) ; 
 TYPE_2__* grid_get_line (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ screen_size_x (struct screen*) ; 

__attribute__((used)) static u_int
window_copy_find_length(struct window_mode_entry *wme, u_int py)
{
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = data->backing;
	struct grid_cell		 gc;
	u_int				 px;

	/*
	 * If the pane has been resized, its grid can contain old overlong
	 * lines. grid_peek_cell does not allow accessing cells beyond the
	 * width of the grid, and screen_write_copy treats them as spaces, so
	 * ignore them here too.
	 */
	px = grid_get_line(s->grid, py)->cellsize;
	if (px > screen_size_x(s))
		px = screen_size_x(s);
	while (px > 0) {
		grid_get_cell(s->grid, px - 1, py, &gc);
		if (gc.data.size != 1 || *gc.data.data != ' ')
			break;
		px--;
	}
	return (px);
}