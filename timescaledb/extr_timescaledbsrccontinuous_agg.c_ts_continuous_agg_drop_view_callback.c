#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  int ContinuousAggViewType ;
typedef  TYPE_1__ ContinuousAgg ;

/* Variables and functions */
#define  ContinuousAggDirectView 130 
#define  ContinuousAggPartialView 129 
#define  ContinuousAggUserView 128 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  drop_continuous_agg (TYPE_1__*,int) ; 
 int /*<<< orphan*/  drop_internal_view (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int ts_continuous_agg_view_type (int /*<<< orphan*/ *,char const*,char const*) ; 

void
ts_continuous_agg_drop_view_callback(ContinuousAgg *ca, const char *schema, const char *name)
{
	ContinuousAggViewType vtyp;
	vtyp = ts_continuous_agg_view_type(&ca->data, schema, name);
	switch (vtyp)
	{
		case ContinuousAggUserView:
			drop_continuous_agg(ca, false /* The user view has already been dropped */);
			break;
		case ContinuousAggPartialView:
		case ContinuousAggDirectView:
			drop_internal_view(ca);
			break;
		default:
			elog(ERROR, "unknown continuous aggregate view type");
	}
}