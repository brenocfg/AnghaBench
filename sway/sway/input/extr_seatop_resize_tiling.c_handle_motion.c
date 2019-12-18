#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct sway_seat {TYPE_2__* cursor; struct seatop_resize_tiling_event* seatop_data; } ;
struct seatop_resize_tiling_event {int ref_lx; int ref_ly; int edge; int h_con_orig_width; int v_con_orig_height; int /*<<< orphan*/  edge_y; TYPE_3__* v_con; int /*<<< orphan*/  edge_x; TYPE_3__* h_con; } ;
struct TYPE_6__ {int width; int height; } ;
struct TYPE_5__ {TYPE_1__* cursor; } ;
struct TYPE_4__ {int x; int y; } ;

/* Variables and functions */
 int WLR_EDGE_BOTTOM ; 
 int WLR_EDGE_LEFT ; 
 int WLR_EDGE_RIGHT ; 
 int WLR_EDGE_TOP ; 
 int /*<<< orphan*/  container_resize_tiled (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handle_motion(struct sway_seat *seat, uint32_t time_msec,
		double dx, double dy) {
	struct seatop_resize_tiling_event *e = seat->seatop_data;
	int amount_x = 0;
	int amount_y = 0;
	int moved_x = seat->cursor->cursor->x - e->ref_lx;
	int moved_y = seat->cursor->cursor->y - e->ref_ly;

	if (e->h_con) {
		if (e->edge & WLR_EDGE_LEFT) {
			amount_x = (e->h_con_orig_width - moved_x) - e->h_con->width;
		} else if (e->edge & WLR_EDGE_RIGHT) {
			amount_x = (e->h_con_orig_width + moved_x) - e->h_con->width;
		}
	}
	if (e->v_con) {
		if (e->edge & WLR_EDGE_TOP) {
			amount_y = (e->v_con_orig_height - moved_y) - e->v_con->height;
		} else if (e->edge & WLR_EDGE_BOTTOM) {
			amount_y = (e->v_con_orig_height + moved_y) - e->v_con->height;
		}
	}

	if (amount_x != 0) {
		container_resize_tiled(e->h_con, e->edge_x, amount_x);
	}
	if (amount_y != 0) {
		container_resize_tiled(e->v_con, e->edge_y, amount_y);
	}
}