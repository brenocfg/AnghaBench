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
typedef  void* u_int ;
struct window {int lastlayout; scalar_t__ id; int /*<<< orphan*/  winlinks; scalar_t__ references; int /*<<< orphan*/  options; void* sy; void* sx; int /*<<< orphan*/ * layout_root; int /*<<< orphan*/ * active; int /*<<< orphan*/  panes; scalar_t__ flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct window*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_w_options ; 
 int /*<<< orphan*/  next_window_id ; 
 int /*<<< orphan*/  options_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_update_activity (struct window*) ; 
 int /*<<< orphan*/  windows ; 
 struct window* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

struct window *
window_create(u_int sx, u_int sy)
{
	struct window	*w;

	w = xcalloc(1, sizeof *w);
	w->name = xstrdup("");
	w->flags = 0;

	TAILQ_INIT(&w->panes);
	w->active = NULL;

	w->lastlayout = -1;
	w->layout_root = NULL;

	w->sx = sx;
	w->sy = sy;

	w->options = options_create(global_w_options);

	w->references = 0;
	TAILQ_INIT(&w->winlinks);

	w->id = next_window_id++;
	RB_INSERT(windows, &windows, w);

	window_update_activity(w);

	return (w);
}