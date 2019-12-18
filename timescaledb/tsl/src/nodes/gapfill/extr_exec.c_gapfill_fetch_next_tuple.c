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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_3__ {int /*<<< orphan*/  gapfill_typid; int /*<<< orphan*/  subslot_time; int /*<<< orphan*/  time_index; int /*<<< orphan*/ * subslot; } ;
typedef  TYPE_1__ GapFillState ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  CustomScanState ;

/* Variables and functions */
 int /*<<< orphan*/  AttrOffsetGetAttrNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * fetch_subplan_tuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gapfill_datum_get_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static TupleTableSlot *
gapfill_fetch_next_tuple(GapFillState *state)
{
	Datum time_value;
	bool isnull;
	TupleTableSlot *subslot = fetch_subplan_tuple((CustomScanState *) state);

	if (!subslot)
		return NULL;

	state->subslot = subslot;
	time_value = slot_getattr(subslot, AttrOffsetGetAttrNumber(state->time_index), &isnull);
	if (isnull)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid time_bucket_gapfill argument: ts cannot be NULL")));

	state->subslot_time = gapfill_datum_get_internal(time_value, state->gapfill_typid);

	return subslot;
}