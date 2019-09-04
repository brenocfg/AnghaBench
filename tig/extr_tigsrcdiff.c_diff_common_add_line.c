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
struct view {int /*<<< orphan*/  lines; } ;
struct line {struct box* data; } ;
struct diff_stat_context {int cells; int /*<<< orphan*/  cell; scalar_t__ cell_text; } ;
struct box_cell {int dummy; } ;
struct box {int cells; int /*<<< orphan*/  cell; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 struct line* add_line_text_at (struct view*,int /*<<< orphan*/ ,char const*,int,int) ; 
 int /*<<< orphan*/  argv_free (scalar_t__) ; 
 char* argv_to_string_alloc (scalar_t__,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct line *
diff_common_add_line(struct view *view, const char *text, enum line_type type, struct diff_stat_context *context)
{
	char *cell_text = context->cell_text ? argv_to_string_alloc(context->cell_text, "") : NULL;
	const char *line_text = cell_text ? cell_text : text;
	struct line *line = add_line_text_at(view, view->lines, line_text, type, context->cells);
	struct box *box;

	free(cell_text);
	argv_free(context->cell_text);

	if (!line)
		return NULL;

	box = line->data;
	if (context->cells)
		memcpy(box->cell, context->cell, sizeof(struct box_cell) * context->cells);
	box->cells = context->cells;
	return line;
}