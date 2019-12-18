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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char const* ddra_fsname; int /*<<< orphan*/ * ddra_result; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ dsl_dataset_rollback_arg_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_dataset_rollback_check ; 
 int /*<<< orphan*/  dsl_dataset_rollback_sync ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int zcp_sync_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
zcp_synctask_rollback(lua_State *state, boolean_t sync, nvlist_t *err_details)
{
	int err;
	const char *dsname = lua_tostring(state, 1);
	dsl_dataset_rollback_arg_t ddra = { 0 };

	ddra.ddra_fsname = dsname;
	ddra.ddra_result = err_details;

	err = zcp_sync_task(state, dsl_dataset_rollback_check,
	    dsl_dataset_rollback_sync, &ddra, sync, dsname);

	return (err);
}