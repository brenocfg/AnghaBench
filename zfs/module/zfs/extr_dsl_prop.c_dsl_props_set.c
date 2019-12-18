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
typedef  int zprop_source_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {char const* dpsa_dsname; int dpsa_source; int /*<<< orphan*/ * dpsa_props; } ;
typedef  TYPE_1__ dsl_props_set_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int ZPROP_SRC_NONE ; 
 int /*<<< orphan*/  dsl_props_set_check ; 
 int /*<<< orphan*/  dsl_props_set_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int fnvlist_num_pairs (int /*<<< orphan*/ *) ; 

int
dsl_props_set(const char *dsname, zprop_source_t source, nvlist_t *props)
{
	dsl_props_set_arg_t dpsa;
	int nblks = 0;

	dpsa.dpsa_dsname = dsname;
	dpsa.dpsa_source = source;
	dpsa.dpsa_props = props;

	/*
	 * If the source includes NONE, then we will only be removing entries
	 * from the ZAP object.  In that case don't check for ENOSPC.
	 */
	if ((source & ZPROP_SRC_NONE) == 0)
		nblks = 2 * fnvlist_num_pairs(props);

	return (dsl_sync_task(dsname, dsl_props_set_check, dsl_props_set_sync,
	    &dpsa, nblks, ZFS_SPACE_CHECK_RESERVED));
}