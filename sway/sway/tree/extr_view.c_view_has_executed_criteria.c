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
struct sway_view {TYPE_1__* executed_criteria; } ;
struct criteria {int dummy; } ;
struct TYPE_2__ {int length; struct criteria** items; } ;

/* Variables and functions */

__attribute__((used)) static bool view_has_executed_criteria(struct sway_view *view,
		struct criteria *criteria) {
	for (int i = 0; i < view->executed_criteria->length; ++i) {
		struct criteria *item = view->executed_criteria->items[i];
		if (item == criteria) {
			return true;
		}
	}
	return false;
}