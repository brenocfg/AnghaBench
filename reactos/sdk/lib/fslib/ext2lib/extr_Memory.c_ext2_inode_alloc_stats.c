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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PEXT2_FILESYS ;

/* Variables and functions */
 int /*<<< orphan*/  ext2_inode_alloc_stats2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ext2_inode_alloc_stats(PEXT2_FILESYS fs, ULONG ino, int inuse)
{
    ext2_inode_alloc_stats2(fs, ino, inuse, 0);
}