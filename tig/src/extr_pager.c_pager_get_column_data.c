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
struct view_column_data {int /*<<< orphan*/  box; int /*<<< orphan*/  text; } ;
struct view {int dummy; } ;
struct line {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  box_text (struct line const*) ; 

bool
pager_get_column_data(struct view *view, const struct line *line, struct view_column_data *column_data)
{
	column_data->text = box_text(line);
	column_data->box = line->data;
	return true;
}