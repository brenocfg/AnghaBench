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
struct TYPE_6__ {TYPE_1__* os_phys; int /*<<< orphan*/ * os_dsl_dataset; } ;
typedef  TYPE_2__ objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_5__ {scalar_t__ os_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ DMU_OST_META ; 
 int /*<<< orphan*/  ZFS_PROP_TYPE ; 
 int /*<<< orphan*/  ZFS_PROP_USERACCOUNTING ; 
 scalar_t__ dmu_objset_userspace_present (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_prop_nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

void
dmu_objset_stats(objset_t *os, nvlist_t *nv)
{
	ASSERT(os->os_dsl_dataset ||
	    os->os_phys->os_type == DMU_OST_META);

	if (os->os_dsl_dataset != NULL)
		dsl_dataset_stats(os->os_dsl_dataset, nv);

	dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_TYPE,
	    os->os_phys->os_type);
	dsl_prop_nvlist_add_uint64(nv, ZFS_PROP_USERACCOUNTING,
	    dmu_objset_userspace_present(os));
}