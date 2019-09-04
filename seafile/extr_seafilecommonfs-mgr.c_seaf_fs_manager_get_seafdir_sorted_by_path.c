#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  entries; } ;
typedef  int /*<<< orphan*/  SeafFSManager ;
typedef  TYPE_1__ SeafDir ;

/* Variables and functions */
 int /*<<< orphan*/  compare_dirents ; 
 int /*<<< orphan*/  g_list_sort (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_dirents_sorted (int /*<<< orphan*/ ) ; 
 TYPE_1__* seaf_fs_manager_get_seafdir_by_path (int /*<<< orphan*/ *,char const*,int,char const*,char const*,int /*<<< orphan*/ *) ; 

SeafDir *
seaf_fs_manager_get_seafdir_sorted_by_path (SeafFSManager *mgr,
                                            const char *repo_id,
                                            int version,
                                            const char *root_id,
                                            const char *path)
{
    SeafDir *dir = seaf_fs_manager_get_seafdir_by_path (mgr, repo_id,
                                                        version, root_id,
                                                        path, NULL);

    if (!dir)
        return NULL;

    /* Only some very old dir objects are not sorted. */
    if (version > 0)
        return dir;

    if (!is_dirents_sorted (dir->entries))
        dir->entries = g_list_sort (dir->entries, compare_dirents);

    return dir;
}