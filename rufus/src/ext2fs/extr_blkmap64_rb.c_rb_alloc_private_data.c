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
struct ext2fs_rb_private {scalar_t__ mark_hit; scalar_t__ test_hit; int /*<<< orphan*/ * wcursor; int /*<<< orphan*/ * rcursor_next; int /*<<< orphan*/ * rcursor; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__* ext2fs_generic_bitmap_64 ;
typedef  scalar_t__ errcode_t ;
struct TYPE_3__ {void* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT ; 
 scalar_t__ ext2fs_get_mem (int,struct ext2fs_rb_private**) ; 

__attribute__((used)) static errcode_t rb_alloc_private_data (ext2fs_generic_bitmap_64 bitmap)
{
	struct ext2fs_rb_private *bp;
	errcode_t	retval;

	retval = ext2fs_get_mem(sizeof (struct ext2fs_rb_private), &bp);
	if (retval)
		return retval;

	bp->root = RB_ROOT;
	bp->rcursor = NULL;
	bp->rcursor_next = NULL;
	bp->wcursor = NULL;

#ifdef ENABLE_BMAP_STATS_OPS
	bp->test_hit = 0;
	bp->mark_hit = 0;
#endif

	bitmap->private = (void *) bp;
	return 0;
}