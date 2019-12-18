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
typedef  int /*<<< orphan*/  SeafFilelockManager ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int update_db (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  update_in_memory (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

int
seaf_filelock_manager_update (SeafFilelockManager *mgr,
                              const char *repo_id,
                              GHashTable *new_locked_files)
{
    update_in_memory (mgr, repo_id, new_locked_files);

    int ret = update_db (mgr, repo_id);

    return ret;
}