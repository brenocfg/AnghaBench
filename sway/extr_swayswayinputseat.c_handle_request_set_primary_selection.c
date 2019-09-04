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
struct wlr_seat_request_set_primary_selection_event {int /*<<< orphan*/  serial; int /*<<< orphan*/  source; } ;
struct wl_listener {int dummy; } ;
struct sway_seat {int /*<<< orphan*/  wlr_seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  request_set_primary_selection ; 
 struct sway_seat* seat ; 
 struct sway_seat* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_set_primary_selection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_request_set_primary_selection(struct wl_listener *listener,
		void *data) {
	struct sway_seat *seat =
		wl_container_of(listener, seat, request_set_primary_selection);
	struct wlr_seat_request_set_primary_selection_event *event = data;
	wlr_seat_set_primary_selection(seat->wlr_seat, event->source, event->serial);
}