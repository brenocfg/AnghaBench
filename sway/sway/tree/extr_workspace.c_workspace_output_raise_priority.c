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
struct sway_workspace {TYPE_1__* output_priority; } ;
struct sway_output {int dummy; } ;
typedef  int /*<<< orphan*/  identifier ;
struct TYPE_3__ {char** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_insert (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  output_get_identifier (char*,int,struct sway_output*) ; 
 char* strdup (char*) ; 
 int workspace_output_get_priority (struct sway_workspace*,struct sway_output*) ; 

void workspace_output_raise_priority(struct sway_workspace *ws,
		struct sway_output *old_output, struct sway_output *output) {
	int old_index = workspace_output_get_priority(ws, old_output);
	if (old_index < 0) {
		return;
	}

	int new_index = workspace_output_get_priority(ws, output);
	if (new_index < 0) {
		char identifier[128];
		output_get_identifier(identifier, sizeof(identifier), output);
		list_insert(ws->output_priority, old_index, strdup(identifier));
	} else if (new_index > old_index) {
		char *name = ws->output_priority->items[new_index];
		list_del(ws->output_priority, new_index);
		list_insert(ws->output_priority, old_index, name);
	}
}