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
struct wlr_surface {int dummy; } ;
struct wlr_presentation_event {int dummy; } ;
struct wlr_box {int dummy; } ;
struct sway_output {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  presentation; } ;

/* Variables and functions */
 TYPE_1__ server ; 
 int /*<<< orphan*/  wlr_presentation_send_surface_presented (int /*<<< orphan*/ ,struct wlr_surface*,struct wlr_presentation_event*) ; 

__attribute__((used)) static void send_presented_iterator(struct sway_output *output,
		struct wlr_surface *surface, struct wlr_box *box, float rotation,
		void *data) {
	struct wlr_presentation_event *event = data;
	wlr_presentation_send_surface_presented(server.presentation,
		surface, event);
}