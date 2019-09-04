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
struct TYPE_5__ {int (* foreach_block ) (TYPE_2__*,char const*,int,int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_4__ {TYPE_2__* backend; } ;
typedef  TYPE_1__ SeafBlockManager ;
typedef  int /*<<< orphan*/  SeafBlockFunc ;

/* Variables and functions */
 int stub1 (TYPE_2__*,char const*,int,int /*<<< orphan*/ ,void*) ; 

int
seaf_block_manager_foreach_block (SeafBlockManager *mgr,
                                  const char *store_id,
                                  int version,
                                  SeafBlockFunc process,
                                  void *user_data)
{
    return mgr->backend->foreach_block (mgr->backend,
                                        store_id, version,
                                        process, user_data);
}