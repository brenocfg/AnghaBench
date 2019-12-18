#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2fs_generic_bitmap_64 ;
typedef  TYPE_2__* ext2fs_ba_private ;
typedef  scalar_t__ errcode_t ;
struct TYPE_7__ {int /*<<< orphan*/  bitarray; } ;
struct TYPE_6__ {int real_end; int start; scalar_t__ private; } ;

/* Variables and functions */
 scalar_t__ ba_alloc_private_data (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static errcode_t ba_copy_bmap(ext2fs_generic_bitmap_64 src,
			      ext2fs_generic_bitmap_64 dest)
{
	ext2fs_ba_private src_bp = (ext2fs_ba_private) src->private;
	ext2fs_ba_private dest_bp;
	errcode_t retval;
	size_t size;

	retval = ba_alloc_private_data (dest);
	if (retval)
		return retval;

	dest_bp = (ext2fs_ba_private) dest->private;

	size = (size_t) (((src->real_end - src->start) / 8) + 1);
	memcpy (dest_bp->bitarray, src_bp->bitarray, size);

	return 0;
}