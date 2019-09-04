#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int lineno; int offset; } ;
struct TYPE_6__ {int lineno; int offset; } ;
struct view {int lines; TYPE_3__ prev_pos; TYPE_2__ pos; TYPE_1__* line; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_position (TYPE_3__*) ; 
 int /*<<< orphan*/  clear_position (TYPE_3__*) ; 

__attribute__((used)) static void
status_restore(struct view *view)
{
	if (!check_position(&view->prev_pos))
		return;

	if (view->prev_pos.lineno >= view->lines)
		view->prev_pos.lineno = view->lines - 1;
	while (view->prev_pos.lineno < view->lines && !view->line[view->prev_pos.lineno].data)
		view->prev_pos.lineno++;
	while (view->prev_pos.lineno > 0 && !view->line[view->prev_pos.lineno].data)
		view->prev_pos.lineno--;

	/* If the above fails, always skip the "On branch" line. */
	if (view->prev_pos.lineno < view->lines)
		view->pos.lineno = view->prev_pos.lineno;
	else
		view->pos.lineno = 1;

	if (view->prev_pos.offset > view->pos.lineno)
		view->pos.offset = view->pos.lineno;
	else if (view->prev_pos.offset < view->lines)
		view->pos.offset = view->prev_pos.offset;

	clear_position(&view->prev_pos);
}