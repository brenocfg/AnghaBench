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
struct ext2fs_rb_private {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__* ext2fs_generic_bitmap_64 ;
struct TYPE_3__ {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_free_mem (struct ext2fs_rb_private**) ; 
 int /*<<< orphan*/  rb_free_tree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rb_free_bmap(ext2fs_generic_bitmap_64 bitmap)
{
	struct ext2fs_rb_private *bp;

	bp = (struct ext2fs_rb_private *) bitmap->private;

	rb_free_tree(&bp->root);
	ext2fs_free_mem(&bp);
	bp = 0;
}