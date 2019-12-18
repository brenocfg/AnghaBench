#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dds_inconsistent; } ;
struct TYPE_5__ {scalar_t__ zc_nvlist_dst; TYPE_4__ zc_objset_stats; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ DMU_OST_ZVOL ; 
 int EIO ; 
 int /*<<< orphan*/  VERIFY0 (int) ; 
 int /*<<< orphan*/  dmu_objset_fast_stat (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dmu_objset_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_objset_type (int /*<<< orphan*/ *) ; 
 int dsl_prop_get_all (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int put_nvlist (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zvol_get_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioc_objset_stats_impl(zfs_cmd_t *zc, objset_t *os)
{
	int error = 0;
	nvlist_t *nv;

	dmu_objset_fast_stat(os, &zc->zc_objset_stats);

	if (zc->zc_nvlist_dst != 0 &&
	    (error = dsl_prop_get_all(os, &nv)) == 0) {
		dmu_objset_stats(os, nv);
		/*
		 * NB: zvol_get_stats() will read the objset contents,
		 * which we aren't supposed to do with a
		 * DS_MODE_USER hold, because it could be
		 * inconsistent.  So this is a bit of a workaround...
		 * XXX reading without owning
		 */
		if (!zc->zc_objset_stats.dds_inconsistent &&
		    dmu_objset_type(os) == DMU_OST_ZVOL) {
			error = zvol_get_stats(os, nv);
			if (error == EIO) {
				nvlist_free(nv);
				return (error);
			}
			VERIFY0(error);
		}
		if (error == 0)
			error = put_nvlist(zc, nv);
		nvlist_free(nv);
	}

	return (error);
}