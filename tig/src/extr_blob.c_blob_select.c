#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lineno; } ;
struct view {TYPE_2__ pos; TYPE_1__* env; struct blob_state* private; } ;
struct line {int dummy; } ;
struct blob_state {scalar_t__ file; } ;
struct TYPE_3__ {scalar_t__ lineno; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  string_format (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
blob_select(struct view *view, struct line *line)
{
	struct blob_state *state = view->private;

	if (state->file)
		string_format(view->env->file, "%s", state->file);
	view->env->lineno = view->pos.lineno + 1;
}