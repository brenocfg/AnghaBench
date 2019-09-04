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
struct wl_listener {int dummy; } ;
struct timespec {int dummy; } ;
struct sway_output {int /*<<< orphan*/  damage; TYPE_1__* wlr_output; int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  damage_frame ; 
 struct sway_output* output ; 
 int /*<<< orphan*/  output_render (struct sway_output*,struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixman_region32_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixman_region32_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_frame_done (struct sway_output*,struct timespec*) ; 
 struct sway_output* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_output_damage_attach_render (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void damage_handle_frame(struct wl_listener *listener, void *data) {
	struct sway_output *output =
		wl_container_of(listener, output, damage_frame);
	if (!output->enabled || !output->wlr_output->enabled) {
		return;
	}

	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);

	bool needs_frame;
	pixman_region32_t damage;
	pixman_region32_init(&damage);
	if (!wlr_output_damage_attach_render(output->damage,
			&needs_frame, &damage)) {
		return;
	}

	if (needs_frame) {
		output_render(output, &now, &damage);
	}

	pixman_region32_fini(&damage);

	// Send frame done to all visible surfaces
	send_frame_done(output, &now);
}