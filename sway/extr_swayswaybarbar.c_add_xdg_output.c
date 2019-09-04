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
struct swaybar_output {int /*<<< orphan*/ * xdg_output; int /*<<< orphan*/  output; TYPE_1__* bar; } ;
struct TYPE_2__ {int /*<<< orphan*/ * xdg_output_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdg_output_listener ; 
 int /*<<< orphan*/ * zxdg_output_manager_v1_get_xdg_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zxdg_output_v1_add_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct swaybar_output*) ; 

__attribute__((used)) static void add_xdg_output(struct swaybar_output *output) {
	if (output->xdg_output != NULL) {
		return;
	}
	assert(output->bar->xdg_output_manager != NULL);
	output->xdg_output = zxdg_output_manager_v1_get_xdg_output(
		output->bar->xdg_output_manager, output->output);
	zxdg_output_v1_add_listener(output->xdg_output, &xdg_output_listener,
		output);
}