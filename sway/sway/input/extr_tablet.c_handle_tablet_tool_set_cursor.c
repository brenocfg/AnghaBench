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
struct wlr_tablet_v2_event_cursor {int /*<<< orphan*/  hotspot_y; int /*<<< orphan*/  hotspot_x; int /*<<< orphan*/  surface; TYPE_4__* seat_client; } ;
struct wlr_surface {int /*<<< orphan*/  resource; } ;
struct wl_listener {int dummy; } ;
struct wl_client {int dummy; } ;
struct sway_tablet_tool {TYPE_1__* seat; } ;
struct sway_cursor {TYPE_5__* seat; } ;
struct TYPE_10__ {TYPE_3__* wlr_seat; } ;
struct TYPE_9__ {struct wl_client* client; } ;
struct TYPE_7__ {struct wlr_surface* focused_surface; } ;
struct TYPE_8__ {TYPE_2__ pointer_state; } ;
struct TYPE_6__ {struct sway_cursor* cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  cursor_set_image_surface (struct sway_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wl_client*) ; 
 int /*<<< orphan*/  seatop_allows_set_cursor (TYPE_5__*) ; 
 int /*<<< orphan*/  set_cursor ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 struct sway_tablet_tool* tool ; 
 struct sway_tablet_tool* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wl_client* wl_resource_get_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tablet_tool_set_cursor(struct wl_listener *listener, void *data) {
	struct sway_tablet_tool *tool =
		wl_container_of(listener, tool, set_cursor);
	struct wlr_tablet_v2_event_cursor *event = data;

	struct sway_cursor *cursor = tool->seat->cursor;
	if (!seatop_allows_set_cursor(cursor->seat)) {
		return;
	}

	struct wl_client *focused_client = NULL;
	struct wlr_surface *focused_surface =
		cursor->seat->wlr_seat->pointer_state.focused_surface;
	if (focused_surface != NULL) {
		focused_client = wl_resource_get_client(focused_surface->resource);
	}

	// TODO: check cursor mode
	if (focused_client == NULL ||
			event->seat_client->client != focused_client) {
		sway_log(SWAY_DEBUG, "denying request to set cursor from unfocused client");
		return;
	}

	cursor_set_image_surface(cursor, event->surface, event->hotspot_x,
			event->hotspot_y, focused_client);
}