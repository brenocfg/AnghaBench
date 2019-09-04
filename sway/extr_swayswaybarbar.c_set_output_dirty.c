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
struct swaybar_output {int dirty; scalar_t__ surface; scalar_t__ frame_scheduled; } ;

/* Variables and functions */
 int /*<<< orphan*/  render_frame (struct swaybar_output*) ; 

__attribute__((used)) static void set_output_dirty(struct swaybar_output *output) {
	if (output->frame_scheduled) {
		output->dirty = true;
	} else if (output->surface) {
		render_frame(output);
	}
}