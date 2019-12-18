#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_15__ {char* za_name; } ;
typedef  TYPE_3__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_16__ {int /*<<< orphan*/  dp_meta_objset; } ;
typedef  TYPE_4__ dsl_pool_t ;
struct TYPE_17__ {scalar_t__ ds_bookmarks_obj; TYPE_2__* ds_dir; int /*<<< orphan*/  ds_object; } ;
typedef  TYPE_5__ dsl_dataset_t ;
struct TYPE_18__ {TYPE_4__* zri_pool; } ;
struct TYPE_14__ {TYPE_1__* dd_pool; } ;
struct TYPE_13__ {int /*<<< orphan*/  dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS_FIELD_BOOKMARK_NAMES ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int dsl_dataset_hold_obj (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  dsl_dataset_is_zapified (TYPE_5__*) ; 
 int /*<<< orphan*/  dsl_dataset_name (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init_serialized (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zap_cursor_serialize (int /*<<< orphan*/ *) ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 TYPE_6__* zcp_run_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zcp_bookmarks_iter(lua_State *state)
{
	char ds_name[ZFS_MAX_DATASET_NAME_LEN];
	char bookmark_name[ZFS_MAX_DATASET_NAME_LEN];
	uint64_t dsobj = lua_tonumber(state, lua_upvalueindex(1));
	uint64_t cursor = lua_tonumber(state, lua_upvalueindex(2));
	dsl_pool_t *dp = zcp_run_info(state)->zri_pool;
	dsl_dataset_t *ds;
	zap_attribute_t za;
	zap_cursor_t zc;

	int err = dsl_dataset_hold_obj(dp, dsobj, FTAG, &ds);
	if (err == ENOENT) {
		return (0);
	} else if (err != 0) {
		return (luaL_error(state,
		    "unexpected error %d from dsl_dataset_hold_obj(dsobj)",
		    err));
	}

	if (!dsl_dataset_is_zapified(ds)) {
		dsl_dataset_rele(ds, FTAG);
		return (0);
	}

	err = zap_lookup(dp->dp_meta_objset, ds->ds_object,
	    DS_FIELD_BOOKMARK_NAMES, sizeof (ds->ds_bookmarks_obj), 1,
	    &ds->ds_bookmarks_obj);
	if (err != 0 && err != ENOENT) {
		dsl_dataset_rele(ds, FTAG);
		return (luaL_error(state,
		    "unexpected error %d from zap_lookup()", err));
	}
	if (ds->ds_bookmarks_obj == 0) {
		dsl_dataset_rele(ds, FTAG);
		return (0);
	}

	/* Store the dataset's name so we can append the bookmark's name */
	dsl_dataset_name(ds, ds_name);

	zap_cursor_init_serialized(&zc, ds->ds_dir->dd_pool->dp_meta_objset,
	    ds->ds_bookmarks_obj, cursor);
	dsl_dataset_rele(ds, FTAG);

	err = zap_cursor_retrieve(&zc, &za);
	if (err != 0) {
		zap_cursor_fini(&zc);
		if (err != ENOENT) {
			return (luaL_error(state,
			    "unexpected error %d from zap_cursor_retrieve()",
			    err));
		}
		return (0);
	}
	zap_cursor_advance(&zc);
	cursor = zap_cursor_serialize(&zc);
	zap_cursor_fini(&zc);

	/* Create the full "pool/fs#bookmark" string to return */
	int n = snprintf(bookmark_name, ZFS_MAX_DATASET_NAME_LEN, "%s#%s",
	    ds_name, za.za_name);
	if (n >= ZFS_MAX_DATASET_NAME_LEN) {
		return (luaL_error(state,
		    "unexpected error %d from snprintf()", ENAMETOOLONG));
	}

	lua_pushnumber(state, cursor);
	lua_replace(state, lua_upvalueindex(2));

	(void) lua_pushstring(state, bookmark_name);
	return (1);
}