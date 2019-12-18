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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZCP_ARG_ARGLIST ; 
 int /*<<< orphan*/  ZCP_ARG_INSTRLIMIT ; 
 int /*<<< orphan*/  ZCP_ARG_MEMLIMIT ; 
 int /*<<< orphan*/  ZCP_ARG_PROGRAM ; 
 int /*<<< orphan*/  ZCP_ARG_SYNC ; 
 int /*<<< orphan*/  ZFS_IOC_CHANNEL_PROGRAM ; 
 int /*<<< orphan*/  fnvlist_add_boolean_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
lzc_channel_program_impl(const char *pool, const char *program, boolean_t sync,
    uint64_t instrlimit, uint64_t memlimit, nvlist_t *argnvl, nvlist_t **outnvl)
{
	int error;
	nvlist_t *args;

	args = fnvlist_alloc();
	fnvlist_add_string(args, ZCP_ARG_PROGRAM, program);
	fnvlist_add_nvlist(args, ZCP_ARG_ARGLIST, argnvl);
	fnvlist_add_boolean_value(args, ZCP_ARG_SYNC, sync);
	fnvlist_add_uint64(args, ZCP_ARG_INSTRLIMIT, instrlimit);
	fnvlist_add_uint64(args, ZCP_ARG_MEMLIMIT, memlimit);
	error = lzc_ioctl(ZFS_IOC_CHANNEL_PROGRAM, pool, args, outnvl);
	fnvlist_free(args);

	return (error);
}