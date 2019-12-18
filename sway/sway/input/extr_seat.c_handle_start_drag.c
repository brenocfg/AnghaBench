#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  destroy; int /*<<< orphan*/  map; int /*<<< orphan*/  unmap; } ;
struct wlr_drag_icon {TYPE_3__ events; TYPE_2__* surface; struct sway_drag_icon* data; } ;
struct wlr_drag {struct wlr_drag_icon* icon; } ;
struct wl_listener {int dummy; } ;
struct sway_seat {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  notify; } ;
struct sway_drag_icon {int /*<<< orphan*/  link; TYPE_4__ destroy; TYPE_4__ map; TYPE_4__ unmap; TYPE_4__ surface_commit; struct wlr_drag_icon* wlr_drag_icon; struct sway_seat* seat; } ;
struct TYPE_10__ {int /*<<< orphan*/  drag_icons; } ;
struct TYPE_6__ {int /*<<< orphan*/  commit; } ;
struct TYPE_7__ {TYPE_1__ events; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 struct sway_drag_icon* calloc (int,int) ; 
 int /*<<< orphan*/  drag_icon_handle_destroy ; 
 int /*<<< orphan*/  drag_icon_handle_map ; 
 int /*<<< orphan*/  drag_icon_handle_surface_commit ; 
 int /*<<< orphan*/  drag_icon_handle_unmap ; 
 int /*<<< orphan*/  drag_icon_update_position (struct sway_drag_icon*) ; 
 TYPE_5__* root ; 
 struct sway_seat* seat ; 
 int /*<<< orphan*/  seatop_begin_default (struct sway_seat*) ; 
 int /*<<< orphan*/  start_drag ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 struct sway_seat* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void handle_start_drag(struct wl_listener *listener, void *data) {
	struct sway_seat *seat = wl_container_of(listener, seat, start_drag);
	struct wlr_drag *wlr_drag = data;
	struct wlr_drag_icon *wlr_drag_icon = wlr_drag->icon;
	if (wlr_drag_icon == NULL) {
		return;
	}

	struct sway_drag_icon *icon = calloc(1, sizeof(struct sway_drag_icon));
	if (icon == NULL) {
		sway_log(SWAY_ERROR, "Allocation failed");
		return;
	}
	icon->seat = seat;
	icon->wlr_drag_icon = wlr_drag_icon;
	wlr_drag_icon->data = icon;

	icon->surface_commit.notify = drag_icon_handle_surface_commit;
	wl_signal_add(&wlr_drag_icon->surface->events.commit, &icon->surface_commit);
	icon->unmap.notify = drag_icon_handle_unmap;
	wl_signal_add(&wlr_drag_icon->events.unmap, &icon->unmap);
	icon->map.notify = drag_icon_handle_map;
	wl_signal_add(&wlr_drag_icon->events.map, &icon->map);
	icon->destroy.notify = drag_icon_handle_destroy;
	wl_signal_add(&wlr_drag_icon->events.destroy, &icon->destroy);

	wl_list_insert(&root->drag_icons, &icon->link);

	drag_icon_update_position(icon);
	seatop_begin_default(seat);
}