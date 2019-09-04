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
struct window_pane {int dummy; } ;
struct window {int /*<<< orphan*/  panes; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct window_pane* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  window_pane_destroy (struct window_pane*) ; 

void
window_destroy_panes(struct window *w)
{
	struct window_pane	*wp;

	while (!TAILQ_EMPTY(&w->panes)) {
		wp = TAILQ_FIRST(&w->panes);
		TAILQ_REMOVE(&w->panes, wp, entry);
		window_pane_destroy(wp);
	}
}