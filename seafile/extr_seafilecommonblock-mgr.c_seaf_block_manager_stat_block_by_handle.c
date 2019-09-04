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
struct TYPE_5__ {int /*<<< orphan*/ * (* stat_block_by_handle ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_2__* backend; } ;
typedef  TYPE_1__ SeafBlockManager ;
typedef  int /*<<< orphan*/  BlockMetadata ;
typedef  int /*<<< orphan*/  BlockHandle ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

BlockMetadata *
seaf_block_manager_stat_block_by_handle (SeafBlockManager *mgr,
                                         BlockHandle *handle)
{
    return mgr->backend->stat_block_by_handle (mgr->backend, handle);
}