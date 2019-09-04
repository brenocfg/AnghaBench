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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  TraverseFSTreeCallback ;
typedef  int /*<<< orphan*/  SeafFSManager ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SHA1 ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int traverse_dir (int /*<<< orphan*/ *,char const*,int,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int
seaf_fs_manager_traverse_tree (SeafFSManager *mgr,
                               const char *repo_id,
                               int version,
                               const char *root_id,
                               TraverseFSTreeCallback callback,
                               void *user_data,
                               gboolean skip_errors)
{
    if (strcmp (root_id, EMPTY_SHA1) == 0) {
        return 0;
    }
    return traverse_dir (mgr, repo_id, version, root_id, callback, user_data, skip_errors);
}