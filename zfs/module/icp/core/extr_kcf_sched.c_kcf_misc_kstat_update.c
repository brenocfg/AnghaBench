#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_23__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_20__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_33__ {TYPE_20__* ks_data; } ;
typedef  TYPE_19__ kstat_t ;
struct TYPE_31__ {int /*<<< orphan*/  ui32; } ;
struct TYPE_32__ {TYPE_17__ value; } ;
struct TYPE_29__ {int /*<<< orphan*/  ui32; } ;
struct TYPE_30__ {TYPE_15__ value; } ;
struct TYPE_27__ {int /*<<< orphan*/  ui32; } ;
struct TYPE_28__ {TYPE_13__ value; } ;
struct TYPE_25__ {int /*<<< orphan*/  ui32; } ;
struct TYPE_26__ {TYPE_11__ value; } ;
struct TYPE_45__ {int /*<<< orphan*/  ui32; } ;
struct TYPE_24__ {TYPE_9__ value; } ;
struct TYPE_43__ {int /*<<< orphan*/  ui32; } ;
struct TYPE_44__ {TYPE_7__ value; } ;
struct TYPE_41__ {int /*<<< orphan*/  ui32; } ;
struct TYPE_42__ {TYPE_5__ value; } ;
struct TYPE_39__ {scalar_t__ ui32; } ;
struct TYPE_40__ {TYPE_3__ value; } ;
struct TYPE_34__ {scalar_t__ ui32; } ;
struct TYPE_38__ {TYPE_1__ value; } ;
struct TYPE_35__ {TYPE_18__ ks_taskq_maxalloc; TYPE_16__ ks_taskq_minalloc; TYPE_14__ ks_taskq_threads; TYPE_12__ ks_swq_maxjobs; TYPE_10__ ks_swq_njobs; TYPE_8__ ks_maxthrs; TYPE_6__ ks_minthrs; TYPE_4__ ks_idle_thrs; TYPE_2__ ks_thrs_in_pool; } ;
typedef  TYPE_20__ kcf_stats_t ;
struct TYPE_37__ {int /*<<< orphan*/  gs_maxjobs; int /*<<< orphan*/  gs_njobs; } ;
struct TYPE_36__ {scalar_t__ kp_threads; scalar_t__ kp_idlethreads; } ;

/* Variables and functions */
 int EACCES ; 
 int KSTAT_WRITE ; 
 int /*<<< orphan*/  crypto_taskq_maxalloc ; 
 int /*<<< orphan*/  crypto_taskq_minalloc ; 
 int /*<<< orphan*/  crypto_taskq_threads ; 
 TYPE_23__* gswq ; 
 int /*<<< orphan*/  kcf_maxthreads ; 
 int /*<<< orphan*/  kcf_minthreads ; 
 TYPE_21__* kcfpool ; 

__attribute__((used)) static int
kcf_misc_kstat_update(kstat_t *ksp, int rw)
{
	uint_t tcnt;
	kcf_stats_t *ks_data;

	if (rw == KSTAT_WRITE)
		return (EACCES);

	ks_data = ksp->ks_data;

	ks_data->ks_thrs_in_pool.value.ui32 = kcfpool->kp_threads;
	/*
	 * The failover thread is counted in kp_idlethreads in
	 * some corner cases. This is done to avoid doing more checks
	 * when submitting a request. We account for those cases below.
	 */
	if ((tcnt = kcfpool->kp_idlethreads) == (kcfpool->kp_threads + 1))
		tcnt--;
	ks_data->ks_idle_thrs.value.ui32 = tcnt;
	ks_data->ks_minthrs.value.ui32 = kcf_minthreads;
	ks_data->ks_maxthrs.value.ui32 = kcf_maxthreads;
	ks_data->ks_swq_njobs.value.ui32 = gswq->gs_njobs;
	ks_data->ks_swq_maxjobs.value.ui32 = gswq->gs_maxjobs;
	ks_data->ks_taskq_threads.value.ui32 = crypto_taskq_threads;
	ks_data->ks_taskq_minalloc.value.ui32 = crypto_taskq_minalloc;
	ks_data->ks_taskq_maxalloc.value.ui32 = crypto_taskq_maxalloc;

	return (0);
}