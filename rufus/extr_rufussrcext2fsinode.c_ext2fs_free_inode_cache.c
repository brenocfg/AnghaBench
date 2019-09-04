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
struct ext2_inode_cache {unsigned int cache_size; scalar_t__ buffer_blk; struct ext2_inode_cache* cache; struct ext2_inode_cache* inode; struct ext2_inode_cache* buffer; scalar_t__ refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_free_mem (struct ext2_inode_cache**) ; 

void ext2fs_free_inode_cache(struct ext2_inode_cache *icache)
{
	unsigned i;

	if (--icache->refcount)
		return;
	if (icache->buffer)
		ext2fs_free_mem(&icache->buffer);
	for (i = 0; i < icache->cache_size; i++)
		ext2fs_free_mem(&icache->cache[i].inode);
	if (icache->cache)
		ext2fs_free_mem(&icache->cache);
	icache->buffer_blk = 0;
	ext2fs_free_mem(&icache);
}