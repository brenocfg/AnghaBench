#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_5__ {scalar_t__ dd_crypto_obj; scalar_t__ dd_object; } ;
typedef  TYPE_1__ dsl_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dsl_dir_get_encryption_root_ddobj (TYPE_1__*,scalar_t__*) ; 
 int dsl_dir_hold (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  zfs_prop_valid_keylocation (char const*,int /*<<< orphan*/ ) ; 

int
dsl_crypto_can_set_keylocation(const char *dsname, const char *keylocation)
{
	int ret = 0;
	dsl_dir_t *dd = NULL;
	dsl_pool_t *dp = NULL;
	uint64_t rddobj;

	/* hold the dsl dir */
	ret = dsl_pool_hold(dsname, FTAG, &dp);
	if (ret != 0)
		goto out;

	ret = dsl_dir_hold(dp, dsname, FTAG, &dd, NULL);
	if (ret != 0) {
		dd = NULL;
		goto out;
	}

	/* if dd is not encrypted, the value may only be "none" */
	if (dd->dd_crypto_obj == 0) {
		if (strcmp(keylocation, "none") != 0) {
			ret = SET_ERROR(EACCES);
			goto out;
		}

		ret = 0;
		goto out;
	}

	/* check for a valid keylocation for encrypted datasets */
	if (!zfs_prop_valid_keylocation(keylocation, B_TRUE)) {
		ret = SET_ERROR(EINVAL);
		goto out;
	}

	/* check that this is an encryption root */
	ret = dsl_dir_get_encryption_root_ddobj(dd, &rddobj);
	if (ret != 0)
		goto out;

	if (rddobj != dd->dd_object) {
		ret = SET_ERROR(EACCES);
		goto out;
	}

	dsl_dir_rele(dd, FTAG);
	dsl_pool_rele(dp, FTAG);

	return (0);

out:
	if (dd != NULL)
		dsl_dir_rele(dd, FTAG);
	if (dp != NULL)
		dsl_pool_rele(dp, FTAG);

	return (ret);
}