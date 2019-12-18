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
struct wlr_box {int width; int height; } ;
struct TYPE_4__ {int floating_minimum_width; int floating_minimum_height; int floating_maximum_width; int floating_maximum_height; } ;
struct TYPE_3__ {int /*<<< orphan*/  output_layout; } ;

/* Variables and functions */
 int INT_MAX ; 
 TYPE_2__* config ; 
 TYPE_1__* root ; 
 struct wlr_box* wlr_output_layout_get_box (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void floating_calculate_constraints(int *min_width, int *max_width,
		int *min_height, int *max_height) {
	if (config->floating_minimum_width == -1) { // no minimum
		*min_width = 0;
	} else if (config->floating_minimum_width == 0) { // automatic
		*min_width = 75;
	} else {
		*min_width = config->floating_minimum_width;
	}

	if (config->floating_minimum_height == -1) { // no minimum
		*min_height = 0;
	} else if (config->floating_minimum_height == 0) { // automatic
		*min_height = 50;
	} else {
		*min_height = config->floating_minimum_height;
	}

	struct wlr_box *box = wlr_output_layout_get_box(root->output_layout, NULL);

	if (config->floating_maximum_width == -1) { // no maximum
		*max_width = INT_MAX;
	} else if (config->floating_maximum_width == 0) { // automatic
		*max_width = box->width;
	} else {
		*max_width = config->floating_maximum_width;
	}

	if (config->floating_maximum_height == -1) { // no maximum
		*max_height = INT_MAX;
	} else if (config->floating_maximum_height == 0) { // automatic
		*max_height = box->height;
	} else {
		*max_height = config->floating_maximum_height;
	}

}