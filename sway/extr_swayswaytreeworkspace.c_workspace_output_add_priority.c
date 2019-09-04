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
struct sway_workspace {int /*<<< orphan*/  output_priority; } ;
struct sway_output {TYPE_1__* wlr_output; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_output ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int list_seq_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

void workspace_output_add_priority(struct sway_workspace *workspace,
		struct sway_output *output) {
	int index = list_seq_find(workspace->output_priority,
			find_output, output->wlr_output->name);
	if (index < 0) {
		list_add(workspace->output_priority, strdup(output->wlr_output->name));
	}
}