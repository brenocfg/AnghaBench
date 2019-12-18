#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int int64_t ;
struct TYPE_9__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_10__ {TYPE_1__ fmds_value; } ;
struct TYPE_11__ {TYPE_2__ ms_accepted; } ;
struct TYPE_13__ {TYPE_3__ mod_stats; TYPE_4__* mod_info; } ;
typedef  TYPE_5__ fmd_module_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* fmdo_recv ) (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,char const*) ;} ;
typedef  TYPE_6__ fmd_hdl_ops_t ;
struct TYPE_15__ {int ev_hrt; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ fmd_event_t ;
struct TYPE_12__ {TYPE_6__* fmdi_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_EREPORT_TIME ; 
 int NANOSEC ; 
 scalar_t__ nvlist_lookup_int64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,char const*) ; 

void
fmd_module_recv(fmd_hdl_t *hdl, nvlist_t *nvl, const char *class)
{
	fmd_module_t *mp = (fmd_module_t *)hdl;
	const fmd_hdl_ops_t *ops = mp->mod_info->fmdi_ops;
	fmd_event_t faux_event = {0};
	int64_t *tv;
	uint_t n;

	/*
	 * Will need to normalized this if we persistently store the case data
	 */
	if (nvlist_lookup_int64_array(nvl, FM_EREPORT_TIME, &tv, &n) == 0)
		faux_event.ev_hrt = tv[0] * NANOSEC + tv[1];
	else
		faux_event.ev_hrt = 0;

	ops->fmdo_recv(hdl, &faux_event, nvl, class);

	mp->mod_stats.ms_accepted.fmds_value.ui64++;

	/* TBD - should we initiate fm_module_gc() periodically? */
}