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

/* Variables and functions */
 int /*<<< orphan*/  cleanup_unused_repo_stores (char*) ; 

__attribute__((used)) static void *
on_start_cleanup_job (void *vdata)
{
    /* recover_interrupted_merges (); */

    /* Ignore migration errors. If any blocks is not migrated successfully,
     * there will be some sync error in run time. The user has to recover the
     * error by resyncing.
     */
    /* migrate_client_v0_repos (); */

    cleanup_unused_repo_stores ("commits");
    cleanup_unused_repo_stores ("fs");
    cleanup_unused_repo_stores ("blocks");

    return vdata;
}