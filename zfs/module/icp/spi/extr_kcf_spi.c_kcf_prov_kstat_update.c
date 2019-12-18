#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_12__* ks_data; scalar_t__ ks_private; } ;
typedef  TYPE_10__ kstat_t ;
struct TYPE_25__ {scalar_t__ ks_nbusy_rval; scalar_t__ ks_nfails; scalar_t__ ks_ndispatches; } ;
struct TYPE_15__ {TYPE_9__ pd_sched_info; } ;
typedef  TYPE_11__ kcf_provider_desc_t ;
struct TYPE_23__ {scalar_t__ ui64; } ;
struct TYPE_24__ {TYPE_7__ value; } ;
struct TYPE_21__ {scalar_t__ ui64; } ;
struct TYPE_22__ {TYPE_5__ value; } ;
struct TYPE_19__ {scalar_t__ ui64; } ;
struct TYPE_20__ {TYPE_3__ value; } ;
struct TYPE_17__ {scalar_t__ ui64; } ;
struct TYPE_18__ {TYPE_1__ value; } ;
struct TYPE_16__ {TYPE_8__ ps_ops_passed; TYPE_6__ ps_ops_busy_rval; TYPE_4__ ps_ops_failed; TYPE_2__ ps_ops_total; } ;
typedef  TYPE_12__ kcf_prov_stats_t ;

/* Variables and functions */
 int EACCES ; 
 int KSTAT_WRITE ; 

__attribute__((used)) static int
kcf_prov_kstat_update(kstat_t *ksp, int rw)
{
	kcf_prov_stats_t *ks_data;
	kcf_provider_desc_t *pd = (kcf_provider_desc_t *)ksp->ks_private;

	if (rw == KSTAT_WRITE)
		return (EACCES);

	ks_data = ksp->ks_data;

	ks_data->ps_ops_total.value.ui64 = pd->pd_sched_info.ks_ndispatches;
	ks_data->ps_ops_failed.value.ui64 = pd->pd_sched_info.ks_nfails;
	ks_data->ps_ops_busy_rval.value.ui64 = pd->pd_sched_info.ks_nbusy_rval;
	ks_data->ps_ops_passed.value.ui64 =
	    pd->pd_sched_info.ks_ndispatches -
	    pd->pd_sched_info.ks_nfails -
	    pd->pd_sched_info.ks_nbusy_rval;

	return (0);
}