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
struct TYPE_3__ {int /*<<< orphan*/  obj_store; } ;
typedef  TYPE_1__ SeafFSManager ;

/* Variables and functions */
 int /*<<< orphan*/  seaf_obj_store_delete_obj (int /*<<< orphan*/ ,char const*,int,char const*) ; 

void
seaf_fs_manager_delete_object (SeafFSManager *mgr,
                               const char *repo_id,
                               int version,
                               const char *id)
{
    seaf_obj_store_delete_obj (mgr->obj_store, repo_id, version, id);
}