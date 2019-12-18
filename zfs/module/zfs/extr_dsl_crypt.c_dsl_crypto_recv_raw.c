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
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {int /*<<< orphan*/  dcrka_do_key; int /*<<< orphan*/ * dcrka_nvl; int /*<<< orphan*/  dcrka_ostype; void* dcrka_fromobj; void* dcrka_dsobj; } ;
typedef  TYPE_1__ dsl_crypto_recv_key_arg_t ;
typedef  int /*<<< orphan*/  dmu_objset_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NORMAL ; 
 int /*<<< orphan*/  dsl_crypto_recv_key_check ; 
 int /*<<< orphan*/  dsl_crypto_recv_key_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int
dsl_crypto_recv_raw(const char *poolname, uint64_t dsobj, uint64_t fromobj,
    dmu_objset_type_t ostype, nvlist_t *nvl, boolean_t do_key)
{
	dsl_crypto_recv_key_arg_t dcrka;

	dcrka.dcrka_dsobj = dsobj;
	dcrka.dcrka_fromobj = fromobj;
	dcrka.dcrka_ostype = ostype;
	dcrka.dcrka_nvl = nvl;
	dcrka.dcrka_do_key = do_key;

	return (dsl_sync_task(poolname, dsl_crypto_recv_key_check,
	    dsl_crypto_recv_key_sync, &dcrka, 1, ZFS_SPACE_CHECK_NORMAL));
}