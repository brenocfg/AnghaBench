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
typedef  int /*<<< orphan*/  SeafFSManager ;
typedef  int /*<<< orphan*/  BlockList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  fill_blocklist ; 
 int seaf_fs_manager_traverse_tree (int /*<<< orphan*/ *,char const*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
seaf_fs_manager_populate_blocklist (SeafFSManager *mgr,
                                    const char *repo_id,
                                    int version,
                                    const char *root_id,
                                    BlockList *bl)
{
    return seaf_fs_manager_traverse_tree (mgr, repo_id, version, root_id,
                                          fill_blocklist,
                                          bl, FALSE);
}