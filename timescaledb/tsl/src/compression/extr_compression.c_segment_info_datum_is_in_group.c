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
struct TYPE_6__ {int* argnull; int isnull; int /*<<< orphan*/ * arg; } ;
struct TYPE_5__ {int is_null; int /*<<< orphan*/  val; TYPE_2__ eq_fcinfo; } ;
typedef  TYPE_1__ SegmentInfo ;
typedef  TYPE_2__ FunctionCallInfoData ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_2__*) ; 

__attribute__((used)) static bool
segment_info_datum_is_in_group(SegmentInfo *segment_info, Datum datum, bool is_null)
{
	Datum data_is_eq;
	FunctionCallInfoData *eq_fcinfo;
	/* if one of the datums is null and the other isn't, we must be in a new group */
	if (segment_info->is_null != is_null)
		return false;

	/* they're both null */
	if (segment_info->is_null)
		return true;

	/* neither is null, call the eq function */
	eq_fcinfo = &segment_info->eq_fcinfo;
	eq_fcinfo->arg[0] = segment_info->val;
	eq_fcinfo->argnull[0] = false;

	eq_fcinfo->arg[1] = datum;
	eq_fcinfo->isnull = false;

	data_is_eq = FunctionCallInvoke(eq_fcinfo);

	if (eq_fcinfo->isnull)
		return false;

	return DatumGetBool(data_is_eq);
}