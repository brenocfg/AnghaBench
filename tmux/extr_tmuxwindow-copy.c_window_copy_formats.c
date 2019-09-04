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
struct TYPE_2__ {int /*<<< orphan*/ * sel; } ;
struct window_copy_mode_data {int /*<<< orphan*/  rectflag; int /*<<< orphan*/  oy; TYPE_1__ screen; } ;
struct format_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_add (struct format_tree*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
window_copy_formats(struct window_mode_entry *wme, struct format_tree *ft)
{
	struct window_copy_mode_data	*data = wme->data;

	format_add(ft, "selection_present", "%d", data->screen.sel != NULL);
	format_add(ft, "scroll_position", "%d", data->oy);
	format_add(ft, "rectangle_toggle", "%d", data->rectflag);
}