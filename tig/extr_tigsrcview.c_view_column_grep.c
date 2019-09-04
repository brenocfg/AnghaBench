#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct view_column_data {int /*<<< orphan*/  refs; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {scalar_t__ refs; } ;
struct TYPE_5__ {TYPE_1__ commit_title; } ;
struct view_column {scalar_t__ type; TYPE_2__ opt; struct view_column* next; } ;
struct view {struct view_column* columns; TYPE_3__* ops; } ;
struct line {int dummy; } ;
struct TYPE_6__ {int (* get_column_data ) (struct view*,struct line*,struct view_column_data*) ;} ;

/* Variables and functions */
 scalar_t__ VIEW_COLUMN_COMMIT_TITLE ; 
 scalar_t__ grep_refs (struct view*,struct view_column*,int /*<<< orphan*/ ) ; 
 scalar_t__ grep_text (struct view*,char const**) ; 
 int stub1 (struct view*,struct line*,struct view_column_data*) ; 
 char const* view_column_text (struct view*,struct view_column_data*,struct view_column*) ; 

bool
view_column_grep(struct view *view, struct line *line)
{
	struct view_column_data column_data = {0};
	bool ok = view->ops->get_column_data(view, line, &column_data);
	struct view_column *column;

	if (!ok)
		return false;

	for (column = view->columns; column; column = column->next) {
		const char *text[] = {
			view_column_text(view, &column_data, column),
			NULL
		};

		if (grep_text(view, text))
			return true;

		if (column->type == VIEW_COLUMN_COMMIT_TITLE &&
		    column->opt.commit_title.refs &&
		    grep_refs(view, column, column_data.refs))
			return true;
	}

	return false;
}