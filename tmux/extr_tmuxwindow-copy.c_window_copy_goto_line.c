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
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {int oy; int /*<<< orphan*/  backing; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int screen_hsize (int /*<<< orphan*/ ) ; 
 int strtonum (char const*,int,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  window_copy_redraw_screen (struct window_mode_entry*) ; 
 int /*<<< orphan*/  window_copy_update_selection (struct window_mode_entry*,int) ; 

__attribute__((used)) static void
window_copy_goto_line(struct window_mode_entry *wme, const char *linestr)
{
	struct window_copy_mode_data	*data = wme->data;
	const char			*errstr;
	int				 lineno;

	lineno = strtonum(linestr, -1, INT_MAX, &errstr);
	if (errstr != NULL)
		return;
	if (lineno < 0 || (u_int)lineno > screen_hsize(data->backing))
		lineno = screen_hsize(data->backing);

	data->oy = lineno;
	window_copy_update_selection(wme, 1);
	window_copy_redraw_screen(wme);
}