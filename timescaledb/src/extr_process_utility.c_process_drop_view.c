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
struct TYPE_3__ {int /*<<< orphan*/  view_name; int /*<<< orphan*/  schema; } ;
typedef  TYPE_1__ EventTriggerDropView ;
typedef  int /*<<< orphan*/  ContinuousAgg ;

/* Variables and functions */
 int /*<<< orphan*/  ts_continuous_agg_drop_view_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_continuous_agg_find_by_view_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_drop_view(EventTriggerDropView *dropped_view)
{
	ContinuousAgg *ca;

	ca = ts_continuous_agg_find_by_view_name(dropped_view->schema, dropped_view->view_name);
	if (ca != NULL)
		ts_continuous_agg_drop_view_callback(ca, dropped_view->schema, dropped_view->view_name);
}