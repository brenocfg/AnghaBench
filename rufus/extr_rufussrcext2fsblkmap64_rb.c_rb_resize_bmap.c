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
struct ext2fs_rb_private {int /*<<< orphan*/  root; int /*<<< orphan*/ * wcursor; int /*<<< orphan*/ * rcursor; } ;
typedef  TYPE_1__* ext2fs_generic_bitmap_64 ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  scalar_t__ __u64 ;
struct TYPE_3__ {scalar_t__ end; scalar_t__ start; scalar_t__ real_end; scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_insert_extent (scalar_t__,scalar_t__,struct ext2fs_rb_private*) ; 
 int /*<<< orphan*/  rb_truncate (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static errcode_t rb_resize_bmap(ext2fs_generic_bitmap_64 bmap,
				__u64 new_end, __u64 new_real_end)
{
	struct ext2fs_rb_private *bp;

	bp = (struct ext2fs_rb_private *) bmap->private;
	bp->rcursor = NULL;
	bp->wcursor = NULL;

	rb_truncate(((new_end < bmap->end) ? new_end : bmap->end) - bmap->start,
		    &bp->root);

	bmap->end = new_end;
	bmap->real_end = new_real_end;

	if (bmap->end < bmap->real_end)
		rb_insert_extent(bmap->end + 1 - bmap->start,
				 bmap->real_end - bmap->end, bp);
	return 0;

}