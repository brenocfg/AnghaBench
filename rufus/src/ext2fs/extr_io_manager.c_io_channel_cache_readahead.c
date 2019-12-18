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
typedef  TYPE_2__* io_channel ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_6__ {TYPE_1__* manager; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cache_readahead ) (TYPE_2__*,unsigned long long,unsigned long long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_OP_NOT_SUPPORTED ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned long long,unsigned long long) ; 

errcode_t io_channel_cache_readahead(io_channel io, unsigned long long block,
				     unsigned long long count)
{
	if (!io->manager->cache_readahead)
		return EXT2_ET_OP_NOT_SUPPORTED;

	return io->manager->cache_readahead(io, block, count);
}