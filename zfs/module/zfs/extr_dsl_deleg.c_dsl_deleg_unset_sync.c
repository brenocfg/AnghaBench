#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_6__ {int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dir_t ;
struct TYPE_7__ {int /*<<< orphan*/ * dda_nvlist; int /*<<< orphan*/  dda_name; } ;
typedef  TYPE_2__ dsl_deleg_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_8__ {scalar_t__ dd_deleg_zapobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_hold (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 TYPE_3__* dsl_dir_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  spa_history_log_internal_dd (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char const*,...) ; 
 scalar_t__ zap_count (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 scalar_t__ zap_destroy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_lookup (int /*<<< orphan*/ *,scalar_t__,char const*,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  zap_remove (int /*<<< orphan*/ *,scalar_t__,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_deleg_unset_sync(void *arg, dmu_tx_t *tx)
{
	dsl_deleg_arg_t *dda = arg;
	dsl_dir_t *dd;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	objset_t *mos = dp->dp_meta_objset;
	nvpair_t *whopair = NULL;
	uint64_t zapobj;

	VERIFY0(dsl_dir_hold(dp, dda->dda_name, FTAG, &dd, NULL));
	zapobj = dsl_dir_phys(dd)->dd_deleg_zapobj;
	if (zapobj == 0) {
		dsl_dir_rele(dd, FTAG);
		return;
	}

	while ((whopair = nvlist_next_nvpair(dda->dda_nvlist, whopair))) {
		const char *whokey = nvpair_name(whopair);
		nvlist_t *perms;
		nvpair_t *permpair = NULL;
		uint64_t jumpobj;

		if (nvpair_value_nvlist(whopair, &perms) != 0) {
			if (zap_lookup(mos, zapobj, whokey, 8,
			    1, &jumpobj) == 0) {
				(void) zap_remove(mos, zapobj, whokey, tx);
				VERIFY(0 == zap_destroy(mos, jumpobj, tx));
			}
			spa_history_log_internal_dd(dd, "permission who remove",
			    tx, "%s", whokey);
			continue;
		}

		if (zap_lookup(mos, zapobj, whokey, 8, 1, &jumpobj) != 0)
			continue;

		while ((permpair = nvlist_next_nvpair(perms, permpair))) {
			const char *perm = nvpair_name(permpair);
			uint64_t n = 0;

			(void) zap_remove(mos, jumpobj, perm, tx);
			if (zap_count(mos, jumpobj, &n) == 0 && n == 0) {
				(void) zap_remove(mos, zapobj,
				    whokey, tx);
				VERIFY(0 == zap_destroy(mos,
				    jumpobj, tx));
			}
			spa_history_log_internal_dd(dd, "permission remove", tx,
			    "%s %s", whokey, perm);
		}
	}
	dsl_dir_rele(dd, FTAG);
}