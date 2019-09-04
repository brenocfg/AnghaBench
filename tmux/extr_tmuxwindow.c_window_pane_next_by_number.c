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
typedef  scalar_t__ u_int ;
struct window_pane {int dummy; } ;
struct window {int /*<<< orphan*/  panes; } ;

/* Variables and functions */
 struct window_pane* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct window_pane* TAILQ_NEXT (struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 

struct window_pane *
window_pane_next_by_number(struct window *w, struct window_pane *wp, u_int n)
{
	for (; n > 0; n--) {
		if ((wp = TAILQ_NEXT(wp, entry)) == NULL)
			wp = TAILQ_FIRST(&w->panes);
	}

	return (wp);
}