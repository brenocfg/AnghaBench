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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_4__ {int n_blocks; int /*<<< orphan*/ * blk_sha1s; } ;
typedef  TYPE_1__ Seafile ;
typedef  int /*<<< orphan*/  SeafFSManager ;
typedef  int /*<<< orphan*/  BlockList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEAF_METADATA_TYPE_FILE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  block_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* seaf_fs_manager_get_seafile (int /*<<< orphan*/ *,char const*,int,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 
 int /*<<< orphan*/  seafile_unref (TYPE_1__*) ; 

__attribute__((used)) static gboolean
fill_blocklist (SeafFSManager *mgr,
                const char *repo_id, int version,
                const char *obj_id, int type,
                void *user_data, gboolean *stop)
{
    BlockList *bl = user_data;
    Seafile *seafile;
    int i;

    if (type == SEAF_METADATA_TYPE_FILE) {
        seafile = seaf_fs_manager_get_seafile (mgr, repo_id, version, obj_id);
        if (!seafile) {
            seaf_warning ("[fs mgr] Failed to find file %s.\n", obj_id);
            return FALSE;
        }

        for (i = 0; i < seafile->n_blocks; ++i)
            block_list_insert (bl, seafile->blk_sha1s[i]);

        seafile_unref (seafile);
    }

    return TRUE;
}