#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* skcka_dsname; int /*<<< orphan*/ * skcka_cp; } ;
typedef  TYPE_1__ spa_keystore_change_key_args_t ;
typedef  int /*<<< orphan*/  dsl_crypto_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_keystore_change_key_check ; 
 int /*<<< orphan*/  spa_keystore_change_key_sync ; 

int
spa_keystore_change_key(const char *dsname, dsl_crypto_params_t *dcp)
{
	spa_keystore_change_key_args_t skcka;

	/* initialize the args struct */
	skcka.skcka_dsname = dsname;
	skcka.skcka_cp = dcp;

	/*
	 * Perform the actual work in syncing context. The blocks modified
	 * here could be calculated but it would require holding the pool
	 * lock and traversing all of the datasets that will have their keys
	 * changed.
	 */
	return (dsl_sync_task(dsname, spa_keystore_change_key_check,
	    spa_keystore_change_key_sync, &skcka, 15,
	    ZFS_SPACE_CHECK_RESERVED));
}