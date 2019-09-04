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
struct wlr_surface {int dummy; } ;
struct wlr_box {int dummy; } ;
struct timespec {int dummy; } ;
struct sway_output {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_surface_send_frame_done (struct wlr_surface*,struct timespec*) ; 

__attribute__((used)) static void send_frame_done_iterator(struct sway_output *output,
		struct wlr_surface *surface, struct wlr_box *box, float rotation,
		void *data) {
	struct timespec *when = data;
	wlr_surface_send_frame_done(surface, when);
}