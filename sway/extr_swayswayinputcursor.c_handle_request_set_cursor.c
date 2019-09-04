#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wlr_surface {int /*<<< orphan*/  resource; } ;
struct wlr_seat_pointer_request_set_cursor_event {int /*<<< orphan*/  hotspot_y; int /*<<< orphan*/  hotspot_x; int /*<<< orphan*/  surface; TYPE_3__* seat_client; } ;
struct wl_listener {int dummy; } ;
struct wl_client {int dummy; } ;
struct sway_cursor {TYPE_4__* seat; } ;
struct TYPE_8__ {TYPE_2__* wlr_seat; } ;
struct TYPE_7__ {struct wl_client* client; } ;
struct TYPE_5__ {struct wlr_surface* focused_surface; } ;
struct TYPE_6__ {TYPE_1__ pointer_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct sway_cursor* cursor ; 
 int /*<<< orphan*/  cursor_set_image_surface (struct sway_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wl_client*) ; 
 int /*<<< orphan*/  request_set_cursor ; 
 int /*<<< orphan*/  seatop_allows_set_cursor (TYPE_4__*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 struct sway_cursor* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wl_client* wl_resource_get_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_request_set_cursor(struct wl_listener *listener,
		void *data) {
	struct sway_cursor *cursor =
		wl_container_of(listener, cursor, request_set_cursor);
	if (!seatop_allows_set_cursor(cursor->seat)) {
		return;
	}
	struct wlr_seat_pointer_request_set_cursor_event *event = data;

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