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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {int /*<<< orphan*/  obj_store; } ;
typedef  TYPE_1__ SeafFSManager ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SHA1 ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seaf_obj_store_obj_exists (int /*<<< orphan*/ ,char const*,int,char const*) ; 

gboolean
seaf_fs_manager_object_exists (SeafFSManager *mgr,
                               const char *repo_id,
                               int version,
                               const char *id)
{
    /* Empty file and dir always exists. */
    if (memcmp (id, EMPTY_SHA1, 40) == 0)
        return TRUE;

    return seaf_obj_store_obj_exists (mgr->obj_store, repo_id, version, id);
}