#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  block_mgr; int /*<<< orphan*/  fs_mgr; } ;
struct TYPE_8__ {int /*<<< orphan*/  ref_cnt_lock; int /*<<< orphan*/  blk_ref_cnts; int /*<<< orphan*/  repo_version; int /*<<< orphan*/  repo_id; } ;
struct TYPE_7__ {int n_blocks; char** blk_sha1s; } ;
typedef  TYPE_1__ Seafile ;
typedef  TYPE_2__ HttpTxTask ;

/* Variables and functions */
 int* g_hash_table_lookup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_5__* seaf ; 
 int /*<<< orphan*/  seaf_block_manager_remove_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* seaf_fs_manager_get_seafile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seafile_unref (TYPE_1__*) ; 

__attribute__((used)) static void
cleanup_file_blocks_http (HttpTxTask *task, const char *file_id)
{
    Seafile *file;
    int i;
    char *block_id;
    int *pcnt;

    file = seaf_fs_manager_get_seafile (seaf->fs_mgr,
                                        task->repo_id, task->repo_version,
                                        file_id);
    if (!file) {
        seaf_warning ("Failed to load seafile object %s:%s\n",
                      task->repo_id, file_id);
        return;
    }

    for (i = 0; i < file->n_blocks; ++i) {
        block_id = file->blk_sha1s[i];

        pthread_mutex_lock (&task->ref_cnt_lock);

        pcnt = g_hash_table_lookup (task->blk_ref_cnts, block_id);
        if (pcnt) {
            --(*pcnt);
            if (*pcnt > 0) {
                pthread_mutex_unlock (&task->ref_cnt_lock);
                continue;
            }
        }

        seaf_block_manager_remove_block (seaf->block_mgr,
                                         task->repo_id, task->repo_version,
                                         block_id);
        g_hash_table_remove (task->blk_ref_cnts, block_id);

        pthread_mutex_unlock (&task->ref_cnt_lock);
    }

    seafile_unref (file);
}