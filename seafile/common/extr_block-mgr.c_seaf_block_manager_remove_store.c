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
struct TYPE_5__ {int (* remove_store ) (TYPE_2__*,char const*) ;} ;
struct TYPE_4__ {TYPE_2__* backend; } ;
typedef  TYPE_1__ SeafBlockManager ;

/* Variables and functions */
 int stub1 (TYPE_2__*,char const*) ; 

int
seaf_block_manager_remove_store (SeafBlockManager *mgr,
                                 const char *store_id)
{
    return mgr->backend->remove_store (mgr->backend, store_id);
}