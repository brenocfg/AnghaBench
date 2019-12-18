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
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  grid; int /*<<< orphan*/ * sel; } ;
struct window_copy_mode_data {char* oy; char* rectflag; char* cx; char* cy; char* selx; char* sely; char* endselx; char* endsely; TYPE_1__ screen; } ;
struct format_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_add (struct format_tree*,char*,char*,char*) ; 
 char* format_grid_line (int /*<<< orphan*/ ,char*) ; 
 char* format_grid_word (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
window_copy_formats(struct window_mode_entry *wme, struct format_tree *ft)
{
	struct window_copy_mode_data	*data = wme->data;
	char				*s;

	format_add(ft, "scroll_position", "%d", data->oy);
	format_add(ft, "rectangle_toggle", "%d", data->rectflag);

	format_add(ft, "copy_cursor_x", "%d", data->cx);
	format_add(ft, "copy_cursor_y", "%d", data->cy);

	format_add(ft, "selection_present", "%d", data->screen.sel != NULL);
	if (data->screen.sel != NULL) {
		format_add(ft, "selection_start_x", "%d", data->selx);
		format_add(ft, "selection_start_y", "%d", data->sely);
		format_add(ft, "selection_end_x", "%d", data->endselx);
		format_add(ft, "selection_end_y", "%d", data->endsely);
	}

	s = format_grid_word(data->screen.grid, data->cx, data->cy);
	if (s != NULL) {
		format_add(ft, "copy_cursor_word", "%s", s);
		free(s);
	}

	s = format_grid_line(data->screen.grid, data->cy);
	if (s != NULL) {
		format_add(ft, "copy_cursor_line", "%s", s);
		free(s);
	}
}