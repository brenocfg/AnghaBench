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
struct sway_output_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  workspaces; } ;
struct sway_output {TYPE_1__ current; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct sway_output_state*,int) ; 
 int /*<<< orphan*/  output_damage_whole (struct sway_output*) ; 

__attribute__((used)) static void apply_output_state(struct sway_output *output,
		struct sway_output_state *state) {
	output_damage_whole(output);
	list_free(output->current.workspaces);
	memcpy(&output->current, state, sizeof(struct sway_output_state));
	output_damage_whole(output);
}