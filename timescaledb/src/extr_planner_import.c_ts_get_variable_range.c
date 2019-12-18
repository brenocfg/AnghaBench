#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_8__ {int /*<<< orphan*/  statsTuple; int /*<<< orphan*/  atttype; } ;
typedef  TYPE_1__ VariableStatData ;
struct TYPE_9__ {int nvalues; int /*<<< orphan*/ * values; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ AttStatsSlot ;

/* Variables and functions */
 int /*<<< orphan*/  ATTSTATSSLOT_VALUES ; 
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  STATISTIC_KIND_HISTOGRAM ; 
 int /*<<< orphan*/  STATISTIC_KIND_MCV ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_attstatsslot (TYPE_2__*) ; 
 scalar_t__ get_actual_variable_range (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_attstatsslot (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_typlenbyval (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  statistic_proc_security_check (TYPE_1__*,int /*<<< orphan*/ ) ; 

bool
ts_get_variable_range(PlannerInfo *root, VariableStatData *vardata, Oid sortop, Datum *min,
					  Datum *max)
{
	Datum tmin = 0;
	Datum tmax = 0;
	bool have_data = false;
	int16 typLen;
	bool typByVal;
	Oid opfuncoid;
	AttStatsSlot sslot;
	int i;

	/*
	 * XXX It's very tempting to try to use the actual column min and max, if
	 * we can get them relatively-cheaply with an index probe.  However, since
	 * this function is called many times during join planning, that could
	 * have unpleasant effects on planning speed.  Need more investigation
	 * before enabling this.
	 */
#ifdef NOT_USED
	if (get_actual_variable_range(root, vardata, sortop, min, max))
		return true;
#endif

	if (!HeapTupleIsValid(vardata->statsTuple))
	{
		/* no stats available, so default result */
		return false;
	}

	/*
	 * If we can't apply the sortop to the stats data, just fail.  In
	 * principle, if there's a histogram and no MCVs, we could return the
	 * histogram endpoints without ever applying the sortop ... but it's
	 * probably not worth trying, because whatever the caller wants to do with
	 * the endpoints would likely fail the security check too.
	 */
	if (!statistic_proc_security_check(vardata, (opfuncoid = get_opcode(sortop))))
		return false;

	get_typlenbyval(vardata->atttype, &typLen, &typByVal);

	/*
	 * If there is a histogram, grab the first and last values.
	 *
	 * If there is a histogram that is sorted with some other operator than
	 * the one we want, fail --- this suggests that there is data we can't
	 * use.
	 */
	if (get_attstatsslot(&sslot,
						 vardata->statsTuple,
						 STATISTIC_KIND_HISTOGRAM,
						 sortop,
						 ATTSTATSSLOT_VALUES))
	{
		if (sslot.nvalues > 0)
		{
			tmin = datumCopy(sslot.values[0], typByVal, typLen);
			tmax = datumCopy(sslot.values[sslot.nvalues - 1], typByVal, typLen);
			have_data = true;
		}
		free_attstatsslot(&sslot);
	}
	else if (get_attstatsslot(&sslot, vardata->statsTuple, STATISTIC_KIND_HISTOGRAM, InvalidOid, 0))
	{
		free_attstatsslot(&sslot);
		return false;
	}

	/*
	 * If we have most-common-values info, look for extreme MCVs.  This is
	 * needed even if we also have a histogram, since the histogram excludes
	 * the MCVs.  However, usually the MCVs will not be the extreme values, so
	 * avoid unnecessary data copying.
	 */
	if (get_attstatsslot(&sslot,
						 vardata->statsTuple,
						 STATISTIC_KIND_MCV,
						 InvalidOid,
						 ATTSTATSSLOT_VALUES))
	{
		bool tmin_is_mcv = false;
		bool tmax_is_mcv = false;
		FmgrInfo opproc;

		fmgr_info(opfuncoid, &opproc);

		for (i = 0; i < sslot.nvalues; i++)
		{
			if (!have_data)
			{
				tmin = tmax = sslot.values[i];
				tmin_is_mcv = tmax_is_mcv = have_data = true;
				continue;
			}
			if (DatumGetBool(
					FunctionCall2Coll(&opproc, DEFAULT_COLLATION_OID, sslot.values[i], tmin)))
			{
				tmin = sslot.values[i];
				tmin_is_mcv = true;
			}
			if (DatumGetBool(
					FunctionCall2Coll(&opproc, DEFAULT_COLLATION_OID, tmax, sslot.values[i])))
			{
				tmax = sslot.values[i];
				tmax_is_mcv = true;
			}
		}
		if (tmin_is_mcv)
			tmin = datumCopy(tmin, typByVal, typLen);
		if (tmax_is_mcv)
			tmax = datumCopy(tmax, typByVal, typLen);
		free_attstatsslot(&sslot);
	}

	*min = tmin;
	*max = tmax;
	return have_data;
}