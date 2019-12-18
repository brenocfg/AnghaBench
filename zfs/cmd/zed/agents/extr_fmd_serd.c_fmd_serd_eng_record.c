#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ hrtime_t ;
struct TYPE_9__ {int sg_flags; scalar_t__ sg_count; scalar_t__ sg_n; scalar_t__ sg_t; int /*<<< orphan*/  sg_name; int /*<<< orphan*/  sg_list; } ;
typedef  TYPE_1__ fmd_serd_eng_t ;
struct TYPE_10__ {scalar_t__ se_hrt; } ;
typedef  TYPE_2__ fmd_serd_elem_t ;

/* Variables and functions */
 int FMD_B_FALSE ; 
 int FMD_B_TRUE ; 
 int FMD_SERD_DIRTY ; 
 int FMD_SERD_FIRED ; 
 scalar_t__ fmd_event_delta (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fmd_serd_eng_discard (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  list_insert_head (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* list_tail (int /*<<< orphan*/ *) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  serd_log_msg (char*,int /*<<< orphan*/ ,...) ; 

int
fmd_serd_eng_record(fmd_serd_eng_t *sgp, hrtime_t hrt)
{
	fmd_serd_elem_t *sep, *oep;

	/*
	 * If the fired flag is already set, return false and discard the
	 * event.  This means that the caller will only see the engine "fire"
	 * once until fmd_serd_eng_reset() is called.  The fmd_serd_eng_fired()
	 * function can also be used in combination with fmd_serd_eng_record().
	 */
	if (sgp->sg_flags & FMD_SERD_FIRED) {
		serd_log_msg("  SERD Engine: record %s already fired!",
		    sgp->sg_name);
		return (FMD_B_FALSE);
	}

	while (sgp->sg_count >= sgp->sg_n)
		fmd_serd_eng_discard(sgp, list_tail(&sgp->sg_list));

	sep = malloc(sizeof (fmd_serd_elem_t));
	sep->se_hrt = hrt;

	list_insert_head(&sgp->sg_list, sep);
	sgp->sg_count++;

	serd_log_msg("  SERD Engine: recording %s of %d (%llu)",
	    sgp->sg_name, (int)sgp->sg_count, (long long unsigned)hrt);

	/*
	 * Pick up the oldest element pointer for comparison to 'sep'.  We must
	 * do this after adding 'sep' because 'oep' and 'sep' can be the same.
	 */
	oep = list_tail(&sgp->sg_list);

	if (sgp->sg_count >= sgp->sg_n &&
	    fmd_event_delta(oep->se_hrt, sep->se_hrt) <= sgp->sg_t) {
		sgp->sg_flags |= FMD_SERD_FIRED | FMD_SERD_DIRTY;
		serd_log_msg("  SERD Engine: fired %s", sgp->sg_name);
		return (FMD_B_TRUE);
	}

	sgp->sg_flags |= FMD_SERD_DIRTY;
	return (FMD_B_FALSE);
}