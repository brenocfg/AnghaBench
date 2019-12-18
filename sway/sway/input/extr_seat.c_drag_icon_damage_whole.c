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
struct sway_drag_icon {int /*<<< orphan*/  y; int /*<<< orphan*/  x; TYPE_1__* wlr_drag_icon; } ;
struct TYPE_2__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  desktop_damage_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void drag_icon_damage_whole(struct sway_drag_icon *icon) {
	if (!icon->wlr_drag_icon->mapped) {
		return;
	}
	desktop_damage_surface(icon->wlr_drag_icon->surface, icon->x, icon->y, true);
}