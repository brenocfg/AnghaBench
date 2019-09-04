#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {TYPE_2__* output_priority; } ;
struct sway_output {TYPE_1__* wlr_output; } ;
struct TYPE_6__ {char** items; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_output ; 
 int /*<<< orphan*/  list_del (TYPE_2__*,int) ; 
 int /*<<< orphan*/  list_insert (TYPE_2__*,int,char*) ; 
 int list_seq_find (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

void workspace_output_raise_priority(struct sway_workspace *ws,
		struct sway_output *old_output, struct sway_output *output) {
	int old_index = list_seq_find(ws->output_priority, find_output,
			old_output->wlr_output->name);
	if (old_index < 0) {
		return;
	}

	int new_index = list_seq_find(ws->output_priority, find_output,
			output->wlr_output->name);
	if (new_index < 0) {
		list_insert(ws->output_priority, old_index,
				strdup(output->wlr_output->name));
	} else if (new_index > old_index) {
		char *name = ws->output_priority->items[new_index];
		list_del(ws->output_priority, new_index);
		list_insert(ws->output_priority, old_index, name);
	}
}