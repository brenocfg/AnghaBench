#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_dataset_space_written (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  parse_written_prop (char const*,char const*,char*) ; 
 int /*<<< orphan*/ * zcp_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int zcp_dataset_hold_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int zcp_handle_error (int /*<<< orphan*/ *,char const*,char*,int) ; 

__attribute__((used)) static int
zcp_get_written_prop(lua_State *state, dsl_pool_t *dp,
    const char *dataset_name, const char *prop_name)
{
	char snap_name[ZFS_MAX_DATASET_NAME_LEN];
	uint64_t used, comp, uncomp;
	dsl_dataset_t *old;
	int error = 0;

	parse_written_prop(dataset_name, prop_name, snap_name);
	dsl_dataset_t *new = zcp_dataset_hold(state, dp, dataset_name, FTAG);
	if (new == NULL)
		return (1); /* not reached; zcp_dataset_hold() longjmp'd */

	error = dsl_dataset_hold(dp, snap_name, FTAG, &old);
	if (error != 0) {
		dsl_dataset_rele(new, FTAG);
		return (zcp_dataset_hold_error(state, dp, snap_name,
		    error));
	}
	error = dsl_dataset_space_written(old, new,
	    &used, &comp, &uncomp);

	dsl_dataset_rele(old, FTAG);
	dsl_dataset_rele(new, FTAG);

	if (error != 0) {
		return (zcp_handle_error(state, dataset_name,
		    snap_name, error));
	}
	(void) lua_pushnumber(state, used);
	(void) lua_pushstring(state, dataset_name);
	return (2);
}