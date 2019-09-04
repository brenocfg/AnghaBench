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
struct view {TYPE_1__* env; int /*<<< orphan*/  pos; scalar_t__ lines; } ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;
struct TYPE_2__ {scalar_t__* blob; scalar_t__* file; int /*<<< orphan*/  commit; } ;

/* Variables and functions */
 int OPEN_RELOAD ; 
 struct view blob_view ; 
 int /*<<< orphan*/  clear_position (int /*<<< orphan*/ *) ; 
 char* open_file_finder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_view (struct view*,struct view*,int) ; 
 int /*<<< orphan*/  string_ncopy (scalar_t__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void
open_blob_view(struct view *prev, enum open_flags flags)
{
	struct view *view = &blob_view;
	bool in_blob_view = prev == view;
	bool has_blob_selection = view->env->blob[0] || view->env->file[0];

	if (!in_blob_view && (view->lines || has_blob_selection)) {
		open_view(prev, view, flags);

	} else {
		const char *file = open_file_finder(view->env->commit);

		if (file) {
			clear_position(&view->pos);
			string_ncopy(view->env->file, file, strlen(file));
			view->env->blob[0] = 0;
			open_view(prev, view, OPEN_RELOAD);
		}
	}
}