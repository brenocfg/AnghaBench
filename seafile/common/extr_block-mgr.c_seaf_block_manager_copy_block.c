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
struct TYPE_5__ {int (* copy ) (TYPE_2__*,char const*,int,char const*,int,char const*) ;} ;
struct TYPE_4__ {TYPE_2__* backend; } ;
typedef  TYPE_1__ SeafBlockManager ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SHA1 ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,char const*,int,char const*,int,char const*) ; 

int
seaf_block_manager_copy_block (SeafBlockManager *mgr,
                               const char *src_store_id,
                               int src_version,
                               const char *dst_store_id,
                               int dst_version,
                               const char *block_id)
{
    if (strcmp (block_id, EMPTY_SHA1) == 0)
        return 0;

    return mgr->backend->copy (mgr->backend,
                               src_store_id,
                               src_version,
                               dst_store_id,
                               dst_version,
                               block_id);
}