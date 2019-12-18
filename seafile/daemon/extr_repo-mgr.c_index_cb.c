#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_2__ {int /*<<< orphan*/  disable_block_hash; int /*<<< orphan*/  fs_mgr; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;

/* Variables and functions */
 TYPE_1__* seaf ; 
 scalar_t__ seaf_fs_manager_index_blocks (int /*<<< orphan*/ ,char const*,int,char const*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 

__attribute__((used)) static int
index_cb (const char *repo_id,
          int version,
          const char *path,
          unsigned char sha1[],
          SeafileCrypt *crypt,
          gboolean write_data)
{
    gint64 size;

    /* Check in blocks and get object ID. */
    if (seaf_fs_manager_index_blocks (seaf->fs_mgr, repo_id, version,
                                      path, sha1, &size, crypt, write_data, !seaf->disable_block_hash) < 0) {
        seaf_warning ("Failed to index file %s.\n", path);
        return -1;
    }
    return 0;
}