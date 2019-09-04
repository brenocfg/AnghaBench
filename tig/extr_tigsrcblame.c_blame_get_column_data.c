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
struct view_column_data {int /*<<< orphan*/  text; int /*<<< orphan*/  commit_title; int /*<<< orphan*/ * date; int /*<<< orphan*/  file_name; int /*<<< orphan*/  author; int /*<<< orphan*/  id; } ;
struct view {int dummy; } ;
struct line {struct blame* data; } ;
struct blame {int /*<<< orphan*/  text; TYPE_1__* commit; } ;
struct TYPE_2__ {int /*<<< orphan*/  title; int /*<<< orphan*/  time; int /*<<< orphan*/  filename; int /*<<< orphan*/  author; int /*<<< orphan*/  id; } ;

/* Variables and functions */

bool
blame_get_column_data(struct view *view, const struct line *line, struct view_column_data *column_data)
{
	struct blame *blame = line->data;

	if (blame->commit) {
		column_data->id = blame->commit->id;
		column_data->author = blame->commit->author;
		column_data->file_name = blame->commit->filename;
		column_data->date = &blame->commit->time;
		column_data->commit_title = blame->commit->title;
	}

	column_data->text = blame->text;

	return true;
}