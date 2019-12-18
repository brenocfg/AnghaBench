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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZCP_ARG_ARGLIST ; 
 int /*<<< orphan*/  ZCP_ARG_INSTRLIMIT ; 
 int /*<<< orphan*/  ZCP_ARG_MEMLIMIT ; 
 int /*<<< orphan*/  ZCP_ARG_PROGRAM ; 
 int /*<<< orphan*/  ZCP_ARG_SYNC ; 
 scalar_t__ ZCP_DEFAULT_INSTRLIMIT ; 
 scalar_t__ ZCP_DEFAULT_MEMLIMIT ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_boolean_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int zcp_eval (char const*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_lua_max_instrlimit ; 
 scalar_t__ zfs_lua_max_memlimit ; 

__attribute__((used)) static int
zfs_ioc_channel_program(const char *poolname, nvlist_t *innvl,
    nvlist_t *outnvl)
{
	char *program;
	uint64_t instrlimit, memlimit;
	boolean_t sync_flag;
	nvpair_t *nvarg = NULL;

	program = fnvlist_lookup_string(innvl, ZCP_ARG_PROGRAM);
	if (0 != nvlist_lookup_boolean_value(innvl, ZCP_ARG_SYNC, &sync_flag)) {
		sync_flag = B_TRUE;
	}
	if (0 != nvlist_lookup_uint64(innvl, ZCP_ARG_INSTRLIMIT, &instrlimit)) {
		instrlimit = ZCP_DEFAULT_INSTRLIMIT;
	}
	if (0 != nvlist_lookup_uint64(innvl, ZCP_ARG_MEMLIMIT, &memlimit)) {
		memlimit = ZCP_DEFAULT_MEMLIMIT;
	}
	nvarg = fnvlist_lookup_nvpair(innvl, ZCP_ARG_ARGLIST);

	if (instrlimit == 0 || instrlimit > zfs_lua_max_instrlimit)
		return (SET_ERROR(EINVAL));
	if (memlimit == 0 || memlimit > zfs_lua_max_memlimit)
		return (SET_ERROR(EINVAL));

	return (zcp_eval(poolname, program, sync_flag, instrlimit, memlimit,
	    nvarg, outnvl));
}