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
typedef  TYPE_1__* io_channel ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_3__ {size_t block_size; int /*<<< orphan*/  align; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_get_mem (size_t,void*) ; 
 int /*<<< orphan*/  ext2fs_get_memalign (size_t,int /*<<< orphan*/ ,void*) ; 

errcode_t io_channel_alloc_buf(io_channel io, int count, void *ptr)
{
	size_t	size;

	if (count == 0)
		size = io->block_size;
	else if (count > 0)
		size = io->block_size * count;
	else
		size = -count;

	if (io->align)
		return ext2fs_get_memalign(size, io->align, ptr);
	else
		return ext2fs_get_mem(size, ptr);
}