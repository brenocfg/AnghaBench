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
struct view_column_data {int /*<<< orphan*/  commit_title; TYPE_1__* ref; int /*<<< orphan*/  id; int /*<<< orphan*/ * date; int /*<<< orphan*/  author; } ;
struct view {int dummy; } ;
struct reference {int /*<<< orphan*/  title; TYPE_1__* ref; int /*<<< orphan*/  time; int /*<<< orphan*/  author; } ;
struct line {struct reference* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */

__attribute__((used)) static bool
refs_get_column_data(struct view *view, const struct line *line, struct view_column_data *column_data)
{
	const struct reference *reference = line->data;

	column_data->author = reference->author;
	column_data->date = &reference->time;
	column_data->id = reference->ref->id;
	column_data->ref = reference->ref;
	column_data->commit_title = reference->title;

	return true;
}