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
struct TYPE_9__ {scalar_t__ sg_count; int sg_flags; scalar_t__ sg_t; int /*<<< orphan*/  sg_list; } ;
typedef  TYPE_1__ fmd_serd_eng_t ;
struct TYPE_10__ {scalar_t__ se_hrt; } ;
typedef  TYPE_2__ fmd_serd_elem_t ;

/* Variables and functions */
 int FMD_SERD_DIRTY ; 
 int FMD_SERD_FIRED ; 
 int /*<<< orphan*/  fmd_serd_eng_discard (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 

void
fmd_serd_eng_gc(fmd_serd_eng_t *sgp)
{
	fmd_serd_elem_t *sep, *nep;
	hrtime_t hrt;

	if (sgp->sg_count == 0 || (sgp->sg_flags & FMD_SERD_FIRED))
		return; /* no garbage collection needed if empty or fired */

	sep = list_head(&sgp->sg_list);
	if (sep == NULL)
		return;

	hrt = sep->se_hrt - sgp->sg_t;

	for (sep = list_head(&sgp->sg_list); sep != NULL; sep = nep) {
		if (sep->se_hrt >= hrt)
			break; /* sep and subsequent events are all within T */

		nep = list_next(&sgp->sg_list, sep);
		fmd_serd_eng_discard(sgp, sep);
		sgp->sg_flags |= FMD_SERD_DIRTY;
	}
}