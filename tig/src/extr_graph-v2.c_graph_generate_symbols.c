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
struct graph_row {int size; struct graph_column* columns; } ;
struct graph_v2 {int position; char* id; int /*<<< orphan*/  colors; struct graph_row parents; struct graph_row next_row; struct graph_row row; struct graph_row prev_row; } ;
struct graph_symbol {int commit; int boundary; int initial; int merge; int parent_right; int matches_commit; int empty; int /*<<< orphan*/  color; int /*<<< orphan*/  new_column; void* shift_left; void* below_shift; void* continue_shift; void* next_right; int /*<<< orphan*/  flanked; int /*<<< orphan*/  below_commit; int /*<<< orphan*/  parent_down; void* continued_up_left; void* continued_left; void* continued_right; void* continued_up; void* continued_down; } ;
struct graph_column {char* id; struct graph_symbol symbol; } ;
struct graph_canvas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  below_commit (int,struct graph_v2*) ; 
 int /*<<< orphan*/  colors_remove_id (int /*<<< orphan*/ *,char*) ; 
 int commits_in_row (struct graph_row*) ; 
 void* continued_down (struct graph_row*,struct graph_row*,int) ; 
 void* continued_left (struct graph_row*,int,int) ; 
 void* continued_right (struct graph_row*,int,int) ; 
 int /*<<< orphan*/  flanked (struct graph_row*,int,int,char*) ; 
 int /*<<< orphan*/  get_color (struct graph_v2*,char const*) ; 
 int /*<<< orphan*/  graph_canvas_append_symbol (struct graph_v2*,struct graph_canvas*,struct graph_symbol*) ; 
 scalar_t__ graph_column_has_commit (struct graph_column*) ; 
 int /*<<< orphan*/  new_column (struct graph_row*,struct graph_row*,int) ; 
 int /*<<< orphan*/  parent_down (struct graph_row*,struct graph_row*,int) ; 
 scalar_t__ parent_right (struct graph_row*,struct graph_row*,struct graph_row*,int) ; 
 void* shift_left (struct graph_row*,struct graph_row*,int) ; 

__attribute__((used)) static void
graph_generate_symbols(struct graph_v2 *graph, struct graph_canvas *canvas)
{
	struct graph_row *prev_row = &graph->prev_row;
	struct graph_row *row = &graph->row;
	struct graph_row *next_row = &graph->next_row;
	struct graph_row *parents = &graph->parents;
	int commits = commits_in_row(parents);
	int initial = commits < 1;
	int merge = commits > 1;
	int pos;

	for (pos = 0; pos < row->size; pos++) {
		struct graph_column *column = &row->columns[pos];
		struct graph_symbol *symbol = &column->symbol;
		const char *id = next_row->columns[pos].id;

		symbol->commit            = (pos == graph->position);
		symbol->boundary          = (pos == graph->position && next_row->columns[pos].symbol.boundary);
		symbol->initial           = initial;
		symbol->merge             = merge;

		symbol->continued_down    = continued_down(row, next_row, pos);
		symbol->continued_up      = continued_down(prev_row, row, pos);
		symbol->continued_right   = continued_right(row, pos, graph->position);
		symbol->continued_left    = continued_left(row, pos, graph->position);
		symbol->continued_up_left = continued_left(prev_row, pos, prev_row->size);

		symbol->parent_down       = parent_down(parents, next_row, pos);
		symbol->parent_right      = (pos > graph->position && parent_right(parents, row, next_row, pos));

		symbol->below_commit      = below_commit(pos, graph);
		symbol->flanked           = flanked(row, pos, graph->position, graph->id);
		symbol->next_right        = continued_right(next_row, pos, 0);
		symbol->matches_commit    = column->id == graph->id;

		symbol->shift_left        = shift_left(row, prev_row, pos);
		symbol->continue_shift    = (pos + 1 < row->size) ? shift_left(row, prev_row, pos + 1) : 0;
		symbol->below_shift       = prev_row->columns[pos].symbol.shift_left;

		symbol->new_column        = new_column(row, prev_row, pos);
		symbol->empty             = (!graph_column_has_commit(&row->columns[pos]));

		if (graph_column_has_commit(column)) {
			id = column->id;
		}
		symbol->color = get_color(graph, id);

		graph_canvas_append_symbol(graph, canvas, symbol);
	}

	colors_remove_id(&graph->colors, graph->id);
}