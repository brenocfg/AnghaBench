#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wl_output {int dummy; } ;
struct swaynag_output {TYPE_1__* swaynag; int /*<<< orphan*/  scale; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  scale; struct swaynag_output* output; } ;

/* Variables and functions */
 int /*<<< orphan*/  render_frame (TYPE_1__*) ; 
 int /*<<< orphan*/  update_cursor (TYPE_1__*) ; 

__attribute__((used)) static void output_scale(void *data, struct wl_output *output,
		int32_t factor) {
	struct swaynag_output *swaynag_output = data;
	swaynag_output->scale = factor;
	if (swaynag_output->swaynag->output == swaynag_output) {
		swaynag_output->swaynag->scale = swaynag_output->scale;
		update_cursor(swaynag_output->swaynag);
		render_frame(swaynag_output->swaynag);
	}
}