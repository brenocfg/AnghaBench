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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  minor_t ;
struct TYPE_3__ {int /*<<< orphan*/  dduha_chkholds; int /*<<< orphan*/  dduha_minor; int /*<<< orphan*/ * dduha_errlist; int /*<<< orphan*/ * dduha_holds; } ;
typedef  TYPE_1__ dsl_dataset_user_hold_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  dsl_dataset_user_hold_check ; 
 int /*<<< orphan*/  dsl_dataset_user_hold_sync ; 
 int dsl_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_num_pairs (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 

int
dsl_dataset_user_hold(nvlist_t *holds, minor_t cleanup_minor, nvlist_t *errlist)
{
	dsl_dataset_user_hold_arg_t dduha;
	nvpair_t *pair;
	int ret;

	pair = nvlist_next_nvpair(holds, NULL);
	if (pair == NULL)
		return (0);

	dduha.dduha_holds = holds;
	/* chkholds can have non-unique name */
	VERIFY(0 == nvlist_alloc(&dduha.dduha_chkholds, 0, KM_SLEEP));
	dduha.dduha_errlist = errlist;
	dduha.dduha_minor = cleanup_minor;

	ret = dsl_sync_task(nvpair_name(pair), dsl_dataset_user_hold_check,
	    dsl_dataset_user_hold_sync, &dduha,
	    fnvlist_num_pairs(holds), ZFS_SPACE_CHECK_RESERVED);
	fnvlist_free(dduha.dduha_chkholds);

	return (ret);
}