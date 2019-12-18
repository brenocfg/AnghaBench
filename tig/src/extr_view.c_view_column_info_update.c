#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct view_column_data {int /*<<< orphan*/ * line_number; int /*<<< orphan*/  reflog; int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {int width; int maxwidth; } ;
struct TYPE_19__ {int width; } ;
struct TYPE_18__ {int width; } ;
struct TYPE_17__ {int width; } ;
struct TYPE_16__ {int width; } ;
struct TYPE_15__ {int width; int maxwidth; } ;
struct TYPE_14__ {int width; } ;
struct TYPE_13__ {int width; int maxwidth; } ;
struct TYPE_11__ {TYPE_9__ ref; TYPE_8__ mode; TYPE_7__ line_number; TYPE_6__ id; TYPE_5__ file_size; TYPE_4__ file_name; TYPE_3__ date; TYPE_2__ author; } ;
struct view_column {int type; int width; TYPE_10__ opt; struct view_column* next; } ;
struct view {int force_redraw; int /*<<< orphan*/  lines; struct view_column* columns; TYPE_1__* ops; } ;
struct line {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* get_column_data ) (struct view*,struct line*,struct view_column_data*) ;} ;

/* Variables and functions */
#define  VIEW_COLUMN_AUTHOR 139 
#define  VIEW_COLUMN_COMMIT_TITLE 138 
#define  VIEW_COLUMN_DATE 137 
#define  VIEW_COLUMN_FILE_NAME 136 
#define  VIEW_COLUMN_FILE_SIZE 135 
#define  VIEW_COLUMN_ID 134 
#define  VIEW_COLUMN_LINE_NUMBER 133 
#define  VIEW_COLUMN_MODE 132 
#define  VIEW_COLUMN_REF 131 
#define  VIEW_COLUMN_SECTION 130 
#define  VIEW_COLUMN_STATUS 129 
#define  VIEW_COLUMN_TEXT 128 
 int count_digits (int /*<<< orphan*/ ) ; 
 int opt_id_width ; 
 int /*<<< orphan*/  stub1 (struct view*,struct line*,struct view_column_data*) ; 
 int utf8_width (char const*) ; 
 char* view_column_text (struct view*,struct view_column_data*,struct view_column*) ; 

bool
view_column_info_update(struct view *view, struct line *line)
{
	struct view_column_data column_data = {0};
	struct view_column *column;
	bool changed = false;

	if (!view->ops->get_column_data(view, line, &column_data))
		return false;

	for (column = view->columns; column; column = column->next) {
		const char *text = view_column_text(view, &column_data, column);
		int width = 0;
		int maxwidth = 0;

		switch (column->type) {
		case VIEW_COLUMN_AUTHOR:
			width = column->opt.author.width;
			maxwidth = width == 0 ? column->opt.author.maxwidth : 0;
			break;

		case VIEW_COLUMN_COMMIT_TITLE:
			break;

		case VIEW_COLUMN_DATE:
			width = column->opt.date.width;
			break;

		case VIEW_COLUMN_FILE_NAME:
			width = column->opt.file_name.width;
			maxwidth = width == 0 ? column->opt.file_name.maxwidth : 0;
			break;

		case VIEW_COLUMN_FILE_SIZE:
			width = column->opt.file_size.width;
			break;

		case VIEW_COLUMN_ID:
			width = column->opt.id.width;
			if (!width)
				width = opt_id_width;
			if (!column_data.reflog && !width)
				width = 7;
			break;

		case VIEW_COLUMN_LINE_NUMBER:
			width = column->opt.line_number.width;
			if (!width) {
				if (column_data.line_number)
					width = count_digits(*column_data.line_number);
				else
					width = count_digits(view->lines);
			}
			if (width < 3)
				width = 3;
			break;

		case VIEW_COLUMN_MODE:
			width = column->opt.mode.width;
			break;

		case VIEW_COLUMN_REF:
			width = column->opt.ref.width;
			maxwidth = width == 0 ? column->opt.ref.maxwidth : 0;
			break;

		case VIEW_COLUMN_SECTION:
			break;

		case VIEW_COLUMN_STATUS:
			break;

		case VIEW_COLUMN_TEXT:
			break;
		}

		if (*text && !width)
			width = utf8_width(text);

		if ((maxwidth > 0) && (width > maxwidth))
			width = maxwidth;

		if (width > column->width) {
			column->width = width;
			changed = true;
		}
	}

	if (changed)
		view->force_redraw = true;
	return changed;
}