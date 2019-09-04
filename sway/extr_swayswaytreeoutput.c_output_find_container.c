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
struct sway_workspace {int dummy; } ;
struct sway_output {TYPE_1__* workspaces; } ;
struct sway_container {int dummy; } ;
struct TYPE_2__ {int length; struct sway_workspace** items; } ;

/* Variables and functions */
 struct sway_container* workspace_find_container (struct sway_workspace*,int (*) (struct sway_container*,void*),void*) ; 

struct sway_container *output_find_container(struct sway_output *output,
		bool (*test)(struct sway_container *con, void *data), void *data) {
	struct sway_container *result = NULL;
	for (int i = 0; i < output->workspaces->length; ++i) {
		struct sway_workspace *workspace = output->workspaces->items[i];
		if ((result = workspace_find_container(workspace, test, data))) {
			return result;
		}
	}
	return NULL;
}