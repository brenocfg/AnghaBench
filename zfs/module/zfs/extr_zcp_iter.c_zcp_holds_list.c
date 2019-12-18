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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_object; int /*<<< orphan*/  ds_is_snapshot; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/ * zri_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int zcp_argerror (int /*<<< orphan*/ *,int,char*,char const*) ; 
 TYPE_1__* zcp_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcp_holds_iter ; 
 TYPE_2__* zcp_run_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zcp_holds_list(lua_State *state)
{
	const char *snapname = lua_tostring(state, 1);
	dsl_pool_t *dp = zcp_run_info(state)->zri_pool;

	dsl_dataset_t *ds = zcp_dataset_hold(state, dp, snapname, FTAG);
	if (ds == NULL)
		return (1); /* not reached; zcp_dataset_hold() longjmp'd */

	boolean_t issnap = ds->ds_is_snapshot;
	uint64_t dsobj = ds->ds_object;
	uint64_t cursor = 0;
	dsl_dataset_rele(ds, FTAG);

	if (!issnap) {
		return (zcp_argerror(state, 1, "%s is not a snapshot",
		    snapname));
	}

	lua_pushnumber(state, dsobj);
	lua_pushnumber(state, cursor);
	lua_pushcclosure(state, &zcp_holds_iter, 2);
	return (1);
}