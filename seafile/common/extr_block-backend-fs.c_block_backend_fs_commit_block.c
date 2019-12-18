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
struct TYPE_3__ {scalar_t__ rw_type; int /*<<< orphan*/  block_id; int /*<<< orphan*/  store_id; int /*<<< orphan*/  tmp_file; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  BlockBackend ;
typedef  TYPE_1__ BHandle ;

/* Variables and functions */
 scalar_t__ BLOCK_WRITE ; 
 int SEAF_PATH_MAX ; 
 scalar_t__ create_parent_path (char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ g_rename (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int,int) ; 
 int /*<<< orphan*/  get_block_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
block_backend_fs_commit_block (BlockBackend *bend,
                               BHandle *handle)
{
    char path[SEAF_PATH_MAX];

    g_return_val_if_fail (handle->rw_type == BLOCK_WRITE, -1);

    get_block_path (bend, handle->block_id, path, handle->store_id, handle->version);

    if (create_parent_path (path) < 0) {
        seaf_warning ("Failed to create path for block %s:%s.\n",
                      handle->store_id, handle->block_id);
        return -1;
    }

    if (g_rename (handle->tmp_file, path) < 0) {
        seaf_warning ("[block bend] failed to commit block %s:%s: %s\n",
                      handle->store_id, handle->block_id, strerror(errno));
        return -1;
    }

    return 0;
}