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
struct view_column_data {int /*<<< orphan*/  file_name; int /*<<< orphan*/ * status; struct view_column* section; } ;
struct TYPE_4__ {char const* text; int type; } ;
struct TYPE_5__ {TYPE_1__ section; } ;
struct view_column {TYPE_2__ opt; int /*<<< orphan*/  type; } ;
struct view {struct line const* line; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct status {TYPE_3__ new; int /*<<< orphan*/  status; } ;
struct line {int type; struct status* data; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 int LINE_DEFAULT ; 
#define  LINE_HEADER 132 
 int LINE_SECTION ; 
#define  LINE_STAT_NONE 131 
#define  LINE_STAT_STAGED 130 
#define  LINE_STAT_UNSTAGED 129 
#define  LINE_STAT_UNTRACKED 128 
 int /*<<< orphan*/  VIEW_COLUMN_SECTION ; 
 int /*<<< orphan*/  opt_status_show_untracked_files ; 
 char* status_onbranch ; 

__attribute__((used)) static bool
status_get_column_data(struct view *view, const struct line *line, struct view_column_data *column_data)
{
	struct status *status = line->data;

	if (!status) {
		static struct view_column group_column;
		const char *text;
		enum line_type type;

		column_data->section = &group_column;
		column_data->section->type = VIEW_COLUMN_SECTION;

		switch (line->type) {
		case LINE_STAT_STAGED:
			type = LINE_SECTION;
			text = "Changes to be committed:";
			break;

		case LINE_STAT_UNSTAGED:
			type = LINE_SECTION;
			text = "Changes not staged for commit:";
			break;

		case LINE_STAT_UNTRACKED:
			type = LINE_SECTION;
			text = "Untracked files:";
			break;

		case LINE_STAT_NONE:
			type = LINE_DEFAULT;
			text = "  (no files)";
			if (!opt_status_show_untracked_files
			    && view->line < line
			    && line[-1].type == LINE_STAT_UNTRACKED)
				text = "  (not shown)";
			break;

		case LINE_HEADER:
			type = LINE_HEADER;
			text = status_onbranch;
			break;

		default:
			return false;
		}

		column_data->section->opt.section.text = text;
		column_data->section->opt.section.type = type;

	} else {
		column_data->status = &status->status;
		column_data->file_name = status->new.name;
	}
	return true;
}