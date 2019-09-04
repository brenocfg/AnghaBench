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
struct wlr_box {int height; int width; int x; int y; } ;
typedef  enum wlr_edges { ____Placeholder_wlr_edges } wlr_edges ;

/* Variables and functions */
#define  WLR_EDGE_BOTTOM 132 
#define  WLR_EDGE_LEFT 131 
#define  WLR_EDGE_NONE 130 
#define  WLR_EDGE_RIGHT 129 
#define  WLR_EDGE_TOP 128 

__attribute__((used)) static void resize_box(struct wlr_box *box, enum wlr_edges edge,
		int thickness) {
	switch (edge) {
	case WLR_EDGE_TOP:
		box->height = thickness;
		break;
	case WLR_EDGE_LEFT:
		box->width = thickness;
		break;
	case WLR_EDGE_RIGHT:
		box->x = box->x + box->width - thickness;
		box->width = thickness;
		break;
	case WLR_EDGE_BOTTOM:
		box->y = box->y + box->height - thickness;
		box->height = thickness;
		break;
	case WLR_EDGE_NONE:
		box->x += thickness;
		box->y += thickness;
		box->width -= thickness * 2;
		box->height -= thickness * 2;
		break;
	}
}