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
struct TYPE_3__ {scalar_t__ top; scalar_t__ right; scalar_t__ bottom; scalar_t__ left; } ;
struct sway_workspace {scalar_t__ layout; scalar_t__ gaps_inner; TYPE_1__ current_gaps; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; TYPE_1__ gaps_outer; } ;
struct sway_seat {int dummy; } ;
struct sway_container {scalar_t__ view; int /*<<< orphan*/  node; } ;
struct TYPE_4__ {scalar_t__ smart_gaps; } ;

/* Variables and functions */
 scalar_t__ L_STACKED ; 
 scalar_t__ L_TABBED ; 
 TYPE_2__* config ; 
 struct sway_seat* input_manager_get_default_seat () ; 
 struct sway_container* seat_get_focus_inactive_tiling (struct sway_seat*,struct sway_workspace*) ; 
 struct sway_container* seat_get_focus_inactive_view (struct sway_seat*,int /*<<< orphan*/ *) ; 
 scalar_t__ view_is_only_visible (scalar_t__) ; 

void workspace_add_gaps(struct sway_workspace *ws) {
	if (ws->current_gaps.top > 0 || ws->current_gaps.right > 0 ||
			ws->current_gaps.bottom > 0 || ws->current_gaps.left > 0) {
		return;
	}
	if (config->smart_gaps) {
		struct sway_seat *seat = input_manager_get_default_seat();
		struct sway_container *focus =
			seat_get_focus_inactive_tiling(seat, ws);
		if (focus && !focus->view) {
			focus = seat_get_focus_inactive_view(seat, &focus->node);
		}
		if (focus && focus->view && view_is_only_visible(focus->view)) {
			return;
		}
	}

	ws->current_gaps = ws->gaps_outer;
	if (ws->layout == L_TABBED || ws->layout == L_STACKED) {
		// We have to add inner gaps for this, because children of tabbed and
		// stacked containers don't apply their own gaps - they assume the
		// tabbed/stacked container is using gaps.
		ws->current_gaps.top += ws->gaps_inner;
		ws->current_gaps.right += ws->gaps_inner;
		ws->current_gaps.bottom += ws->gaps_inner;
		ws->current_gaps.left += ws->gaps_inner;
	}

	ws->x += ws->current_gaps.left;
	ws->y += ws->current_gaps.top;
	ws->width -= ws->current_gaps.left + ws->current_gaps.right;
	ws->height -= ws->current_gaps.top + ws->current_gaps.bottom;
}