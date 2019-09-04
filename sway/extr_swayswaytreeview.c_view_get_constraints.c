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
struct sway_view {TYPE_1__* impl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_constraints ) (struct sway_view*,double*,double*,double*,double*) ;} ;

/* Variables and functions */
 double DBL_MAX ; 
 double DBL_MIN ; 
 int /*<<< orphan*/  stub1 (struct sway_view*,double*,double*,double*,double*) ; 

void view_get_constraints(struct sway_view *view, double *min_width,
		double *max_width, double *min_height, double *max_height) {
	if (view->impl->get_constraints) {
		view->impl->get_constraints(view,
				min_width, max_width, min_height, max_height);
	} else {
		*min_width = DBL_MIN;
		*max_width = DBL_MAX;
		*min_height = DBL_MIN;
		*max_height = DBL_MAX;
	}
}