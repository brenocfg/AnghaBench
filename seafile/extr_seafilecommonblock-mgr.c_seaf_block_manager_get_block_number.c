#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  guint64 ;
typedef  int /*<<< orphan*/  SeafBlockManager ;

/* Variables and functions */
 int /*<<< orphan*/  get_block_number ; 
 int /*<<< orphan*/  seaf_block_manager_foreach_block (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

guint64
seaf_block_manager_get_block_number (SeafBlockManager *mgr,
                                     const char *store_id,
                                     int version)
{
    guint64 n_blocks = 0;

    seaf_block_manager_foreach_block (mgr, store_id, version,
                                      get_block_number, &n_blocks);

    return n_blocks;
}