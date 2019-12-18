#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  ds_is_snapshot; } ;
typedef  TYPE_1__ dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dsl_dataset_space_wouldfree (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
zfs_ioc_space_snaps(const char *lastsnap, nvlist_t *innvl, nvlist_t *outnvl)
{
	int error;
	dsl_pool_t *dp;
	dsl_dataset_t *new, *old;
	char *firstsnap;
	uint64_t used, comp, uncomp;

	firstsnap = fnvlist_lookup_string(innvl, "firstsnap");

	error = dsl_pool_hold(lastsnap, FTAG, &dp);
	if (error != 0)
		return (error);

	error = dsl_dataset_hold(dp, lastsnap, FTAG, &new);
	if (error == 0 && !new->ds_is_snapshot) {
		dsl_dataset_rele(new, FTAG);
		error = SET_ERROR(EINVAL);
	}
	if (error != 0) {
		dsl_pool_rele(dp, FTAG);
		return (error);
	}
	error = dsl_dataset_hold(dp, firstsnap, FTAG, &old);
	if (error == 0 && !old->ds_is_snapshot) {
		dsl_dataset_rele(old, FTAG);
		error = SET_ERROR(EINVAL);
	}
	if (error != 0) {
		dsl_dataset_rele(new, FTAG);
		dsl_pool_rele(dp, FTAG);
		return (error);
	}

	error = dsl_dataset_space_wouldfree(old, new, &used, &comp, &uncomp);
	dsl_dataset_rele(old, FTAG);
	dsl_dataset_rele(new, FTAG);
	dsl_pool_rele(dp, FTAG);
	fnvlist_add_uint64(outnvl, "used", used);
	fnvlist_add_uint64(outnvl, "compressed", comp);
	fnvlist_add_uint64(outnvl, "uncompressed", uncomp);
	return (error);
}