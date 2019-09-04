#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
struct TYPE_7__ {TYPE_2__* icache; } ;
struct TYPE_6__ {unsigned int cache_size; scalar_t__ buffer_blk; TYPE_1__* cache; } ;
struct TYPE_5__ {scalar_t__ ino; } ;

/* Variables and functions */

errcode_t ext2fs_flush_icache(ext2_filsys fs)
{
	unsigned	i;

	if (!fs->icache)
		return 0;

	for (i=0; i < fs->icache->cache_size; i++)
		fs->icache->cache[i].ino = 0;

	fs->icache->buffer_blk = 0;
	return 0;
}