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
typedef  int /*<<< orphan*/  uint32_t ;
struct swaybar_tray {TYPE_2__* bar; TYPE_4__* items; } ;
struct swaybar_sni {int dummy; } ;
struct swaybar_output {int output_x; int output_y; scalar_t__ output_height; TYPE_1__* bar; } ;
struct swaybar_hotspot {int dummy; } ;
struct TYPE_7__ {int left; int top; int bottom; } ;
struct swaybar_config {int position; TYPE_3__ gaps; } ;
typedef  enum hotspot_event_handling { ____Placeholder_hotspot_event_handling } hotspot_event_handling ;
struct TYPE_8__ {struct swaybar_sni** items; } ;
struct TYPE_6__ {struct swaybar_config* config; } ;
struct TYPE_5__ {struct swaybar_tray* tray; } ;

/* Variables and functions */
 int HOTSPOT_IGNORE ; 
 int HOTSPOT_PROCESS ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP ; 
 int /*<<< orphan*/  cmp_sni_id ; 
 int /*<<< orphan*/  handle_click (struct swaybar_sni*,int,int,int /*<<< orphan*/ ,int) ; 
 int list_seq_find (TYPE_4__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static enum hotspot_event_handling icon_hotspot_callback(
		struct swaybar_output *output, struct swaybar_hotspot *hotspot,
		int x, int y, uint32_t button, void *data) {
	sway_log(SWAY_DEBUG, "Clicked on %s", (char *)data);

	struct swaybar_tray *tray = output->bar->tray;
	int idx = list_seq_find(tray->items, cmp_sni_id, data);

	if (idx != -1) {
		struct swaybar_sni *sni = tray->items->items[idx];
		// guess global position since wayland doesn't expose it
		struct swaybar_config *config = tray->bar->config;
		int global_x = output->output_x + config->gaps.left + x;
		bool top_bar = config->position & ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP;
		int global_y = output->output_y + (top_bar ? config->gaps.top + y:
				(int) output->output_height - config->gaps.bottom - y);

		sway_log(SWAY_DEBUG, "Guessing click position at (%d, %d)", global_x, global_y);
		handle_click(sni, global_x, global_y, button, 1); // TODO get delta from event
		return HOTSPOT_IGNORE;
	} else {
		sway_log(SWAY_DEBUG, "but it doesn't exist");
	}

	return HOTSPOT_PROCESS;
}