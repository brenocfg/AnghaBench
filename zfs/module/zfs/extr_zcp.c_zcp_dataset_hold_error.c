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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int EXDEV ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  spa_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcp_argerror (int /*<<< orphan*/ *,int,char*,char const*,...) ; 

int
zcp_dataset_hold_error(lua_State *state, dsl_pool_t *dp, const char *dsname,
    int error)
{
	if (error == ENOENT) {
		(void) zcp_argerror(state, 1, "no such dataset '%s'", dsname);
		return (0); /* not reached; zcp_argerror will longjmp */
	} else if (error == EXDEV) {
		(void) zcp_argerror(state, 1,
		    "dataset '%s' is not in the target pool '%s'",
		    dsname, spa_name(dp->dp_spa));
		return (0); /* not reached; zcp_argerror will longjmp */
	} else if (error == EIO) {
		(void) luaL_error(state,
		    "I/O error while accessing dataset '%s'", dsname);
		return (0); /* not reached; luaL_error will longjmp */
	} else if (error != 0) {
		(void) luaL_error(state,
		    "unexpected error %d while accessing dataset '%s'",
		    error, dsname);
		return (0); /* not reached; luaL_error will longjmp */
	}
	return (0);
}