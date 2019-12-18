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
struct sway_output {scalar_t__ damage; scalar_t__ wlr_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_output_damage_add_whole (scalar_t__) ; 

void output_damage_whole(struct sway_output *output) {
	// The output can exist with no wlr_output if it's just been disconnected
	// and the transaction to evacuate it has't completed yet.
	if (output && output->wlr_output && output->damage) {
		wlr_output_damage_add_whole(output->damage);
	}
}