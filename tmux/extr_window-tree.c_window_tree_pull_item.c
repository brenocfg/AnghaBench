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
struct winlink {TYPE_1__* window; } ;
struct window_tree_itemdata {scalar_t__ type; int /*<<< orphan*/  pane; int /*<<< orphan*/  winlink; int /*<<< orphan*/  session; } ;
struct window_pane {int dummy; } ;
struct session {int /*<<< orphan*/  windows; struct winlink* curw; } ;
struct TYPE_2__ {struct window_pane* active; } ;

/* Variables and functions */
 scalar_t__ WINDOW_TREE_SESSION ; 
 scalar_t__ WINDOW_TREE_WINDOW ; 
 struct session* session_find_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_has_pane (TYPE_1__*,struct window_pane*) ; 
 struct window_pane* window_pane_find_by_id (int /*<<< orphan*/ ) ; 
 struct winlink* winlink_find_by_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
window_tree_pull_item(struct window_tree_itemdata *item, struct session **sp,
    struct winlink **wlp, struct window_pane **wp)
{
	*wp = NULL;
	*wlp = NULL;
	*sp = session_find_by_id(item->session);
	if (*sp == NULL)
		return;
	if (item->type == WINDOW_TREE_SESSION) {
		*wlp = (*sp)->curw;
		*wp = (*wlp)->window->active;
		return;
	}

	*wlp = winlink_find_by_index(&(*sp)->windows, item->winlink);
	if (*wlp == NULL) {
		*sp = NULL;
		return;
	}
	if (item->type == WINDOW_TREE_WINDOW) {
		*wp = (*wlp)->window->active;
		return;
	}

	*wp = window_pane_find_by_id(item->pane);
	if (!window_has_pane((*wlp)->window, *wp))
		*wp = NULL;
	if (*wp == NULL) {
		*sp = NULL;
		*wlp = NULL;
		return;
	}
}