#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zbm_creation_txg; } ;
typedef  TYPE_1__ zfs_bookmark_phys_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXDEV ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dsl_bookmark_hold_ds (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char**) ; 
 int dsl_bookmark_lookup_impl (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dataset_is_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dsl_bookmark_lookup(dsl_pool_t *dp, const char *fullname,
    dsl_dataset_t *later_ds, zfs_bookmark_phys_t *bmp)
{
	char *shortname;
	dsl_dataset_t *ds;
	int error;

	error = dsl_bookmark_hold_ds(dp, fullname, &ds, FTAG, &shortname);
	if (error != 0)
		return (error);

	error = dsl_bookmark_lookup_impl(ds, shortname, bmp);
	if (error == 0 && later_ds != NULL) {
		if (!dsl_dataset_is_before(later_ds, ds, bmp->zbm_creation_txg))
			error = SET_ERROR(EXDEV);
	}
	dsl_dataset_rele(ds, FTAG);
	return (error);
}