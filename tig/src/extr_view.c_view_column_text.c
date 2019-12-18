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
struct view_column_data {char* commit_title; char* file_name; char* reflog; char* id; char* text; TYPE_10__* section; int /*<<< orphan*/ * status; int /*<<< orphan*/ * mode; int /*<<< orphan*/ * file_size; TYPE_3__* ref; int /*<<< orphan*/  date; int /*<<< orphan*/  author; } ;
struct TYPE_17__ {int /*<<< orphan*/  display; } ;
struct TYPE_16__ {int /*<<< orphan*/  display; } ;
struct TYPE_15__ {int /*<<< orphan*/  display; } ;
struct TYPE_13__ {int /*<<< orphan*/  format; int /*<<< orphan*/  local; int /*<<< orphan*/  display; } ;
struct TYPE_12__ {int /*<<< orphan*/  display; int /*<<< orphan*/  width; } ;
struct TYPE_18__ {TYPE_6__ status; TYPE_5__ id; TYPE_4__ file_size; TYPE_2__ date; TYPE_1__ author; } ;
struct view_column {int type; TYPE_7__ opt; } ;
struct view {int dummy; } ;
struct TYPE_19__ {char* text; } ;
struct TYPE_20__ {TYPE_8__ section; } ;
struct TYPE_14__ {char* name; } ;
struct TYPE_11__ {TYPE_9__ opt; } ;

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
 char* mkauthor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mkdate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mkfilesize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mkmode (int /*<<< orphan*/ ) ; 
 char* mkstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
view_column_text(struct view *view, struct view_column_data *column_data,
		 struct view_column *column)
{
	const char *text = "";

	switch (column->type) {
	case VIEW_COLUMN_AUTHOR:
		if (column_data->author)
			text = mkauthor(column_data->author, column->opt.author.width, column->opt.author.display);
		break;

	case VIEW_COLUMN_COMMIT_TITLE:
		text = column_data->commit_title;
		break;

	case VIEW_COLUMN_DATE:
		if (column_data->date)
			text = mkdate(column_data->date, column->opt.date.display,
				      column->opt.date.local, column->opt.date.format);
		break;

	case VIEW_COLUMN_REF:
		if (column_data->ref)
			text = column_data->ref->name;
		break;

	case VIEW_COLUMN_FILE_NAME:
		if (column_data->file_name)
			text = column_data->file_name;
		break;

	case VIEW_COLUMN_FILE_SIZE:
		if (column_data->file_size)
			text = mkfilesize(*column_data->file_size, column->opt.file_size.display);
		break;

	case VIEW_COLUMN_ID:
		if (column->opt.id.display)
			text = column_data->reflog ? column_data->reflog : column_data->id;
		break;

	case VIEW_COLUMN_LINE_NUMBER:
		break;

	case VIEW_COLUMN_MODE:
		if (column_data->mode)
			text = mkmode(*column_data->mode);
		break;

	case VIEW_COLUMN_STATUS:
		if (column_data->status)
			text = mkstatus(*column_data->status, column->opt.status.display);
		break;

	case VIEW_COLUMN_SECTION:
		text = column_data->section->opt.section.text;
		break;

	case VIEW_COLUMN_TEXT:
		text = column_data->text;
		break;
	}

	return text ? text : "";
}