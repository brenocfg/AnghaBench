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
typedef  int /*<<< orphan*/  uint32_t ;
struct swaybar_output {TYPE_1__* bar; } ;
struct swaybar_hotspot {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct status_line {int dummy; } ;
struct i3bar_block {int dummy; } ;
typedef  enum hotspot_event_handling { ____Placeholder_hotspot_event_handling } hotspot_event_handling ;
struct TYPE_2__ {struct status_line* status; } ;

/* Variables and functions */
 int i3bar_block_send_click (struct status_line*,struct i3bar_block*,int,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum hotspot_event_handling block_hotspot_callback(
		struct swaybar_output *output, struct swaybar_hotspot *hotspot,
		int x, int y, uint32_t button, void *data) {
	struct i3bar_block *block = data;
	struct status_line *status = output->bar->status;
	return i3bar_block_send_click(status, block, x, y, x - hotspot->x,
			y - hotspot->y, hotspot->width, hotspot->height, button);
}