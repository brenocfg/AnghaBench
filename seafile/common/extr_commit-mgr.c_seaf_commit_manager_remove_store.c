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
typedef  TYPE_1__ SeafCommitManager ;

/* Variables and functions */
 int seaf_obj_store_remove_store (int /*<<< orphan*/ ,char const*) ; 

int
seaf_commit_manager_remove_store (SeafCommitManager *mgr,
                                  const char *store_id)
{
    return seaf_obj_store_remove_store (mgr->obj_store, store_id);
}