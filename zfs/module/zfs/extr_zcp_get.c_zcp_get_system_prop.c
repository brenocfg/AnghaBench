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
typedef  int /*<<< orphan*/  zfs_prop_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_special_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int get_zap_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prop_valid_for_ds (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zcp_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int zcp_handle_error (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 char* zfs_prop_to_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zcp_get_system_prop(lua_State *state, dsl_pool_t *dp, const char *dataset_name,
    zfs_prop_t zfs_prop)
{
	int error;
	/*
	 * zcp_dataset_hold will either successfully return the requested
	 * dataset or throw a lua error and longjmp out of the zfs.get_prop call
	 * without returning.
	 */
	dsl_dataset_t *ds = zcp_dataset_hold(state, dp, dataset_name, FTAG);
	if (ds == NULL)
		return (1); /* not reached; zcp_dataset_hold() longjmp'd */

	/* Check that the property is valid for the given dataset */
	const char *prop_name = zfs_prop_to_name(zfs_prop);
	if (!prop_valid_for_ds(ds, zfs_prop)) {
		dsl_dataset_rele(ds, FTAG);
		return (0);
	}

	/* Check if the property can be accessed directly */
	error = get_special_prop(state, ds, dataset_name, zfs_prop);
	if (error == 0) {
		dsl_dataset_rele(ds, FTAG);
		/* The value and source have been pushed by get_special_prop */
		return (2);
	}
	if (error != ENOENT) {
		dsl_dataset_rele(ds, FTAG);
		return (zcp_handle_error(state, dataset_name,
		    prop_name, error));
	}

	/* If we were unable to find it, look in the zap object */
	error = get_zap_prop(state, ds, zfs_prop);
	dsl_dataset_rele(ds, FTAG);
	if (error != 0) {
		return (zcp_handle_error(state, dataset_name,
		    prop_name, error));
	}
	/* The value and source have been pushed by get_zap_prop */
	return (2);
}