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
struct view_column_data {int /*<<< orphan*/  refs; int /*<<< orphan*/ * graph_canvas; int /*<<< orphan*/  graph; int /*<<< orphan*/  commit_title; int /*<<< orphan*/  reflog; int /*<<< orphan*/  id; int /*<<< orphan*/ * date; int /*<<< orphan*/  author; } ;
struct view {struct main_state* private; } ;
struct main_state {int /*<<< orphan*/  graph; scalar_t__ with_graph; int /*<<< orphan*/ * reflog; scalar_t__ reflogs; } ;
struct line {int lineno; struct commit* data; } ;
struct commit {int /*<<< orphan*/  graph; int /*<<< orphan*/  title; int /*<<< orphan*/  id; int /*<<< orphan*/  time; int /*<<< orphan*/  author; } ;

/* Variables and functions */
 int /*<<< orphan*/  main_get_commit_refs (struct line const*,struct commit*) ; 

bool
main_get_column_data(struct view *view, const struct line *line, struct view_column_data *column_data)
{
	struct main_state *state = view->private;
	struct commit *commit = line->data;

	column_data->author = commit->author;
	column_data->date = &commit->time;
	column_data->id = commit->id;
	if (state->reflogs)
		column_data->reflog = state->reflog[line->lineno - 1];

	column_data->commit_title = commit->title;
	if (state->with_graph) {
		column_data->graph = state->graph;
		column_data->graph_canvas = &commit->graph;
	}

	column_data->refs = main_get_commit_refs(line, commit);

	return true;
}