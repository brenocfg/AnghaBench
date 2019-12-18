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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 char* ZCP_ARG_ARGLIST ; 
 int /*<<< orphan*/  ZCP_RET_ERROR ; 
 int /*<<< orphan*/  ZCP_RET_RETURN ; 
 int /*<<< orphan*/  fnvlist_add_boolean_value (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvpair_value_int64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int zcp_eval (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*) ; 
 int /*<<< orphan*/  zfs_lua_max_memlimit ; 

int
dsl_destroy_snapshots_nvl(nvlist_t *snaps, boolean_t defer,
    nvlist_t *errlist)
{
	if (nvlist_next_nvpair(snaps, NULL) == NULL)
		return (0);

	/*
	 * lzc_destroy_snaps() is documented to take an nvlist whose
	 * values "don't matter".  We need to convert that nvlist to
	 * one that we know can be converted to LUA. We also don't
	 * care about any duplicate entries because the nvlist will
	 * be converted to a LUA table which should take care of this.
	 */
	nvlist_t *snaps_normalized;
	VERIFY0(nvlist_alloc(&snaps_normalized, 0, KM_SLEEP));
	for (nvpair_t *pair = nvlist_next_nvpair(snaps, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(snaps, pair)) {
		fnvlist_add_boolean_value(snaps_normalized,
		    nvpair_name(pair), B_TRUE);
	}

	nvlist_t *arg;
	VERIFY0(nvlist_alloc(&arg, 0, KM_SLEEP));
	fnvlist_add_nvlist(arg, "snaps", snaps_normalized);
	fnvlist_free(snaps_normalized);
	fnvlist_add_boolean_value(arg, "defer", defer);

	nvlist_t *wrapper;
	VERIFY0(nvlist_alloc(&wrapper, 0, KM_SLEEP));
	fnvlist_add_nvlist(wrapper, ZCP_ARG_ARGLIST, arg);
	fnvlist_free(arg);

	const char *program =
	    "arg = ...\n"
	    "snaps = arg['snaps']\n"
	    "defer = arg['defer']\n"
	    "errors = { }\n"
	    "has_errors = false\n"
	    "for snap, v in pairs(snaps) do\n"
	    "    errno = zfs.check.destroy{snap, defer=defer}\n"
	    "    zfs.debug('snap: ' .. snap .. ' errno: ' .. errno)\n"
	    "    if errno == ENOENT then\n"
	    "        snaps[snap] = nil\n"
	    "    elseif errno ~= 0 then\n"
	    "        errors[snap] = errno\n"
	    "        has_errors = true\n"
	    "    end\n"
	    "end\n"
	    "if has_errors then\n"
	    "    return errors\n"
	    "end\n"
	    "for snap, v in pairs(snaps) do\n"
	    "    errno = zfs.sync.destroy{snap, defer=defer}\n"
	    "    assert(errno == 0)\n"
	    "end\n"
	    "return { }\n";

	nvlist_t *result = fnvlist_alloc();
	int error = zcp_eval(nvpair_name(nvlist_next_nvpair(snaps, NULL)),
	    program,
	    B_TRUE,
	    0,
	    zfs_lua_max_memlimit,
	    nvlist_next_nvpair(wrapper, NULL), result);
	if (error != 0) {
		char *errorstr = NULL;
		(void) nvlist_lookup_string(result, ZCP_RET_ERROR, &errorstr);
		if (errorstr != NULL) {
			zfs_dbgmsg(errorstr);
		}
		return (error);
	}
	fnvlist_free(wrapper);

	/*
	 * lzc_destroy_snaps() is documented to fill the errlist with
	 * int32 values, so we need to convert the int64 values that are
	 * returned from LUA.
	 */
	int rv = 0;
	nvlist_t *errlist_raw = fnvlist_lookup_nvlist(result, ZCP_RET_RETURN);
	for (nvpair_t *pair = nvlist_next_nvpair(errlist_raw, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(errlist_raw, pair)) {
		int32_t val = (int32_t)fnvpair_value_int64(pair);
		if (rv == 0)
			rv = val;
		fnvlist_add_int32(errlist, nvpair_name(pair), val);
	}
	fnvlist_free(result);
	return (rv);
}