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
struct wlr_box {scalar_t__ height; scalar_t__ width; scalar_t__ y; scalar_t__ x; } ;
struct sway_view {TYPE_2__* surface; } ;
struct TYPE_3__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_4__ {TYPE_1__ current; } ;

/* Variables and functions */

__attribute__((used)) static void get_geometry(struct sway_view *view, struct wlr_box *box) {
	box->x = box->y = 0;
	if (view->surface) {
		box->width = view->surface->current.width;
		box->height = view->surface->current.height;
	} else {
		box->width = 0;
		box->height = 0;
	}
}