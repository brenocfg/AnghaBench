#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2fs_generic_bitmap_64 ;
typedef  TYPE_2__* ext2fs_ba_private ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ __u64 ;
struct TYPE_5__ {scalar_t__ bitarray; } ;
struct TYPE_4__ {scalar_t__ end; scalar_t__ real_end; scalar_t__ start; int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_clear_bit64 (scalar_t__,scalar_t__) ; 
 scalar_t__ ext2fs_resize_mem (size_t,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static errcode_t ba_resize_bmap(ext2fs_generic_bitmap_64 bmap,
				__u64 new_end, __u64 new_real_end)
{
	ext2fs_ba_private bp = (ext2fs_ba_private) bmap->private;
	errcode_t	retval;
	size_t		size, new_size;
	__u64		bitno;

	/*
	 * If we're expanding the bitmap, make sure all of the new
	 * parts of the bitmap are zero.
	 */
	if (new_end > bmap->end) {
		bitno = bmap->real_end;
		if (bitno > new_end)
			bitno = new_end;
		for (; bitno > bmap->end; bitno--)
			ext2fs_clear_bit64(bitno - bmap->start, bp->bitarray);
	}
	if (new_real_end == bmap->real_end) {
		bmap->end = new_end;
		return 0;
	}

	size = ((bmap->real_end - bmap->start) / 8) + 1;
	new_size = ((new_real_end - bmap->start) / 8) + 1;

	if (size != new_size) {
		retval = ext2fs_resize_mem(size, new_size, &bp->bitarray);
		if (retval)
			return retval;
	}
	if (new_size > size)
		memset(bp->bitarray + size, 0, new_size - size);

	bmap->end = new_end;
	bmap->real_end = new_real_end;
	return 0;

}