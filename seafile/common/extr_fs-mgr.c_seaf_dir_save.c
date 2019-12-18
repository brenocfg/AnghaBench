#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ondisk_size; int /*<<< orphan*/  ondisk; int /*<<< orphan*/  dir_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  obj_store; } ;
typedef  TYPE_1__ SeafFSManager ;
typedef  TYPE_2__ SeafDir ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SHA1 ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ seaf_obj_store_write_obj (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
seaf_dir_save (SeafFSManager *fs_mgr,
               const char *repo_id,
               int version,
               SeafDir *dir)
{
    int ret = 0;

    /* Don't need to save empty dir on disk. */
    if (memcmp (dir->dir_id, EMPTY_SHA1, 40) == 0)
        return 0;

    if (seaf_obj_store_write_obj (fs_mgr->obj_store, repo_id, version, dir->dir_id,
                                  dir->ondisk, dir->ondisk_size, FALSE) < 0)
        ret = -1;

    return ret;
}