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
typedef  int /*<<< orphan*/  uint32_t ;
struct sway_view {TYPE_1__* impl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_int_prop ) (struct sway_view*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VIEW_PROP_WINDOW_TYPE ; 
 int /*<<< orphan*/  stub1 (struct sway_view*,int /*<<< orphan*/ ) ; 

uint32_t view_get_window_type(struct sway_view *view) {
	if (view->impl->get_int_prop) {
		return view->impl->get_int_prop(view, VIEW_PROP_WINDOW_TYPE);
	}
	return 0;
}