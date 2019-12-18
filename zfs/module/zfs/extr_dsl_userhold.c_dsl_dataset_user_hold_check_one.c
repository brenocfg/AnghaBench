#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_5__ {int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {scalar_t__ ds_userrefs_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  EEXIST ; 
 int ENOENT ; 
 scalar_t__ MAXNAMELEN ; 
 scalar_t__ MAX_TAG_PREFIX_LEN ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 TYPE_3__* dsl_dataset_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_config_held (TYPE_1__*) ; 
 scalar_t__ strlen (char const*) ; 
 int zap_lookup (int /*<<< orphan*/ *,scalar_t__,char const*,int,int,int /*<<< orphan*/ *) ; 

int
dsl_dataset_user_hold_check_one(dsl_dataset_t *ds, const char *htag,
    boolean_t temphold, dmu_tx_t *tx)
{
	dsl_pool_t *dp = dmu_tx_pool(tx);
	objset_t *mos = dp->dp_meta_objset;
	int error = 0;

	ASSERT(dsl_pool_config_held(dp));

	if (strlen(htag) > MAXNAMELEN)
		return (SET_ERROR(E2BIG));
	/* Tempholds have a more restricted length */
	if (temphold && strlen(htag) + MAX_TAG_PREFIX_LEN >= MAXNAMELEN)
		return (SET_ERROR(E2BIG));

	/* tags must be unique (if ds already exists) */
	if (ds != NULL && dsl_dataset_phys(ds)->ds_userrefs_obj != 0) {
		uint64_t value;

		error = zap_lookup(mos, dsl_dataset_phys(ds)->ds_userrefs_obj,
		    htag, 8, 1, &value);
		if (error == 0)
			error = SET_ERROR(EEXIST);
		else if (error == ENOENT)
			error = 0;
	}

	return (error);
}