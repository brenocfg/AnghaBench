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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int dsl_dataset_hold (int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zcp_dataset_hold_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int) ; 

dsl_dataset_t *
zcp_dataset_hold(lua_State *state, dsl_pool_t *dp, const char *dsname,
    void *tag)
{
	dsl_dataset_t *ds;
	int error = dsl_dataset_hold(dp, dsname, tag, &ds);
	(void) zcp_dataset_hold_error(state, dp, dsname, error);
	return (ds);
}