#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* remove_block ) (TYPE_2__*,char const*,int,char const*) ;} ;
struct TYPE_4__ {TYPE_2__* backend; } ;
typedef  TYPE_1__ SeafBlockManager ;

/* Variables and functions */
 int /*<<< orphan*/  is_object_id_valid (char const*) ; 
 int /*<<< orphan*/  is_uuid_valid (char const*) ; 
 int stub1 (TYPE_2__*,char const*,int,char const*) ; 

int
seaf_block_manager_remove_block (SeafBlockManager *mgr,
                                 const char *store_id,
                                 int version,
                                 const char *block_id)
{
    if (!store_id || !is_uuid_valid(store_id) ||
        !block_id || !is_object_id_valid(block_id))
        return -1;

    return mgr->backend->remove_block (mgr->backend, store_id, version, block_id);
}