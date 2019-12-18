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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wlr_presentation_event {int /*<<< orphan*/  flags; int /*<<< orphan*/  seq; int /*<<< orphan*/  refresh; int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  output; } ;
struct wlr_output_event_present {int /*<<< orphan*/  flags; int /*<<< orphan*/  seq; int /*<<< orphan*/  refresh; TYPE_1__* when; } ;
struct wl_listener {int dummy; } ;
struct sway_output {int /*<<< orphan*/  wlr_output; int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 struct sway_output* output ; 
 int /*<<< orphan*/  output_for_each_surface (struct sway_output*,int /*<<< orphan*/ ,struct wlr_presentation_event*) ; 
 int /*<<< orphan*/  present ; 
 int /*<<< orphan*/  send_presented_iterator ; 
 struct sway_output* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_present(struct wl_listener *listener, void *data) {
	struct sway_output *output = wl_container_of(listener, output, present);
	struct wlr_output_event_present *output_event = data;

	if (!output->enabled) {
		return;
	}

	struct wlr_presentation_event event = {
		.output = output->wlr_output,
		.tv_sec = (uint64_t)output_event->when->tv_sec,
		.tv_nsec = (uint32_t)output_event->when->tv_nsec,
		.refresh = (uint32_t)output_event->refresh,
		.seq = (uint64_t)output_event->seq,
		.flags = output_event->flags,
	};
	output_for_each_surface(output, send_presented_iterator, &event);
}