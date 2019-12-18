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
struct TYPE_3__ {int /*<<< orphan*/  dbda_success; int /*<<< orphan*/ * dbda_errors; int /*<<< orphan*/ * dbda_bmarks; } ;
typedef  TYPE_1__ dsl_bookmark_destroy_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  dsl_bookmark_destroy_check ; 
 int /*<<< orphan*/  dsl_bookmark_destroy_sync ; 
 int dsl_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_num_pairs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 

int
dsl_bookmark_destroy(nvlist_t *bmarks, nvlist_t *errors)
{
	int rv;
	dsl_bookmark_destroy_arg_t dbda;
	nvpair_t *pair = nvlist_next_nvpair(bmarks, NULL);
	if (pair == NULL)
		return (0);

	dbda.dbda_bmarks = bmarks;
	dbda.dbda_errors = errors;
	dbda.dbda_success = fnvlist_alloc();

	rv = dsl_sync_task(nvpair_name(pair), dsl_bookmark_destroy_check,
	    dsl_bookmark_destroy_sync, &dbda, fnvlist_num_pairs(bmarks),
	    ZFS_SPACE_CHECK_RESERVED);
	fnvlist_free(dbda.dbda_success);
	return (rv);
}