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
struct wl_listener {int dummy; } ;
struct timespec {int dummy; } ;
struct TYPE_7__ {struct sway_container* fullscreen; } ;
struct sway_workspace {TYPE_3__ current; } ;
struct TYPE_6__ {struct sway_workspace* active_workspace; } ;
struct sway_output {int /*<<< orphan*/  damage; TYPE_2__ current; TYPE_1__* wlr_output; int /*<<< orphan*/  enabled; } ;
struct sway_container {scalar_t__ view; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_8__ {struct sway_container* fullscreen_global; } ;
struct TYPE_5__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  damage_frame ; 
 struct sway_output* output ; 
 int /*<<< orphan*/  output_render (struct sway_output*,struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixman_region32_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixman_region32_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* root ; 
 int scan_out_fullscreen_view (struct sway_output*,scalar_t__) ; 
 int /*<<< orphan*/  send_frame_done (struct sway_output*,struct timespec*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
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

	struct sway_workspace *workspace = output->current.active_workspace;
	if (workspace == NULL) {
		return;
	}

	struct sway_container *fullscreen_con = root->fullscreen_global;
	if (!fullscreen_con) {
		fullscreen_con = workspace->current.fullscreen;
	}

	if (fullscreen_con && fullscreen_con->view) {
		// Try to scan-out the fullscreen view
		static bool last_scanned_out = false;
		bool scanned_out =
			scan_out_fullscreen_view(output, fullscreen_con->view);

		if (scanned_out && !last_scanned_out) {
			sway_log(SWAY_DEBUG, "Scanning out fullscreen view");
		}
		if (last_scanned_out && !scanned_out) {
			sway_log(SWAY_DEBUG, "Stopping fullscreen view scan out");
		}
		last_scanned_out = scanned_out;

		if (scanned_out) {
			goto frame_done;
		}
	}

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

frame_done:
	// Send frame done to all visible surfaces
	send_frame_done(output, &now);
}