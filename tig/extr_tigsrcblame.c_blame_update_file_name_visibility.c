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
struct TYPE_3__ {scalar_t__ display; } ;
struct TYPE_4__ {TYPE_1__ file_name; } ;
struct view_column {int hidden; TYPE_2__ opt; } ;
struct view {struct blame_state* private; } ;
struct blame_state {int /*<<< orphan*/  auto_filename_display; } ;

/* Variables and functions */
 scalar_t__ FILENAME_AUTO ; 
 scalar_t__ FILENAME_NO ; 
 int /*<<< orphan*/  VIEW_COLUMN_FILE_NAME ; 
 struct view_column* get_view_column (struct view*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
blame_update_file_name_visibility(struct view *view)
{
	struct blame_state *state = view->private;
	struct view_column *column = get_view_column(view, VIEW_COLUMN_FILE_NAME);

	if (!column)
		return;

	column->hidden = column->opt.file_name.display == FILENAME_NO ||
			 (column->opt.file_name.display == FILENAME_AUTO &&
			  !state->auto_filename_display);
}