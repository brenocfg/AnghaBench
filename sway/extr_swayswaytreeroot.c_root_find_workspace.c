#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {int dummy; } ;
struct sway_output {int dummy; } ;
struct TYPE_4__ {TYPE_1__* outputs; } ;
struct TYPE_3__ {int length; struct sway_output** items; } ;

/* Variables and functions */
 struct sway_workspace* output_find_workspace (struct sway_output*,int (*) (struct sway_workspace*,void*),void*) ; 
 TYPE_2__* root ; 

struct sway_workspace *root_find_workspace(
		bool (*test)(struct sway_workspace *ws, void *data), void *data) {
	struct sway_workspace *result = NULL;
	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		if ((result = output_find_workspace(output, test, data))) {
			return result;
		}
	}
	return NULL;
}