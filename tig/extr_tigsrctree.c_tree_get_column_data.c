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
struct view_column_data {int /*<<< orphan*/  file_name; int /*<<< orphan*/ * mode; int /*<<< orphan*/  id; int /*<<< orphan*/ * file_size; int /*<<< orphan*/ * date; int /*<<< orphan*/  author; } ;
struct view {int dummy; } ;
struct tree_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  mode; int /*<<< orphan*/  commit; int /*<<< orphan*/  size; int /*<<< orphan*/  time; int /*<<< orphan*/  author; } ;
struct line {scalar_t__ type; struct tree_entry* data; } ;

/* Variables and functions */
 scalar_t__ LINE_DIRECTORY ; 
 scalar_t__ LINE_HEADER ; 

__attribute__((used)) static bool
tree_get_column_data(struct view *view, const struct line *line, struct view_column_data *column_data)
{
	const struct tree_entry *entry = line->data;

	if (line->type == LINE_HEADER)
		return false;

	column_data->author = entry->author;
	column_data->date = &entry->time;
	if (line->type != LINE_DIRECTORY)
		column_data->file_size = &entry->size;
	column_data->id = entry->commit;
	column_data->mode = &entry->mode;
	column_data->file_name = entry->name;

	return true;
}