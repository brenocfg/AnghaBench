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
typedef  int /*<<< orphan*/  SeafCommitManager ;
typedef  int /*<<< orphan*/  CommitTraverseFunc ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  traverse_commit_tree_common (int /*<<< orphan*/ *,char const*,int,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

gboolean
seaf_commit_manager_traverse_commit_tree (SeafCommitManager *mgr,
                                          const char *repo_id,
                                          int version,
                                          const char *head,
                                          CommitTraverseFunc func,
                                          void *data,
                                          gboolean skip_errors)
{
    return traverse_commit_tree_common (mgr, repo_id, version, head,
                                        func, data, skip_errors, FALSE);
}