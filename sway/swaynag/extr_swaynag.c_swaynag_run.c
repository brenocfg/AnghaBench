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
struct swaynag {int run_display; scalar_t__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  render_frame (struct swaynag*) ; 
 int /*<<< orphan*/  wl_display_disconnect (scalar_t__) ; 
 int wl_display_dispatch (scalar_t__) ; 

void swaynag_run(struct swaynag *swaynag) {
	swaynag->run_display = true;
	render_frame(swaynag);
	while (swaynag->run_display
			&& wl_display_dispatch(swaynag->display) != -1) {
		// This is intentionally left blank
	}

	if (swaynag->display) {
		wl_display_disconnect(swaynag->display);
	}
}