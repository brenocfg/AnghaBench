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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ dsl_crypto_params_t ;
typedef  int /*<<< orphan*/  dmu_objset_type_t ;
typedef  int /*<<< orphan*/  dmu_objset_create_sync_func_t ;
struct TYPE_6__ {char const* doca_name; TYPE_1__* doca_dcp; int /*<<< orphan*/  doca_type; void* doca_userarg; int /*<<< orphan*/  doca_userfunc; int /*<<< orphan*/  doca_flags; int /*<<< orphan*/  doca_cred; } ;
typedef  TYPE_2__ dmu_objset_create_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRED () ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NORMAL ; 
 int /*<<< orphan*/  dmu_objset_create_check ; 
 int /*<<< orphan*/  dmu_objset_create_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ) ; 

int
dmu_objset_create(const char *name, dmu_objset_type_t type, uint64_t flags,
    dsl_crypto_params_t *dcp, dmu_objset_create_sync_func_t func, void *arg)
{
	dmu_objset_create_arg_t doca;
	dsl_crypto_params_t tmp_dcp = { 0 };

	doca.doca_name = name;
	doca.doca_cred = CRED();
	doca.doca_flags = flags;
	doca.doca_userfunc = func;
	doca.doca_userarg = arg;
	doca.doca_type = type;

	/*
	 * Some callers (mostly for testing) do not provide a dcp on their
	 * own but various code inside the sync task will require it to be
	 * allocated. Rather than adding NULL checks throughout this code
	 * or adding dummy dcp's to all of the callers we simply create a
	 * dummy one here and use that. This zero dcp will have the same
	 * effect as asking for inheritance of all encryption params.
	 */
	doca.doca_dcp = (dcp != NULL) ? dcp : &tmp_dcp;

	return (dsl_sync_task(name,
	    dmu_objset_create_check, dmu_objset_create_sync, &doca,
	    6, ZFS_SPACE_CHECK_NORMAL));
}