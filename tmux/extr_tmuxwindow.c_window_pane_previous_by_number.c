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
 struct window_pane* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct window_pane* TAILQ_PREV (struct window_pane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  window_panes ; 

struct window_pane *
window_pane_previous_by_number(struct window *w, struct window_pane *wp,
    u_int n)
{
	for (; n > 0; n--) {
		if ((wp = TAILQ_PREV(wp, window_panes, entry)) == NULL)
			wp = TAILQ_LAST(&w->panes, window_panes);
	}

	return (wp);
}