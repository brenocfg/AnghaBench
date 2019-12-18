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
typedef  int /*<<< orphan*/  errcode_t ;
typedef  int __u64 ;
struct TYPE_5__ {scalar_t__ bitarray; } ;
struct TYPE_4__ {int start; int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ext2fs_test_bit64 (unsigned long,scalar_t__) ; 

__attribute__((used)) static errcode_t ba_find_first_zero(ext2fs_generic_bitmap_64 bitmap,
				    __u64 start, __u64 end, __u64 *out)
{
	ext2fs_ba_private bp = (ext2fs_ba_private)bitmap->private;
	unsigned long bitpos = start - bitmap->start;
	unsigned long count = end - start + 1;
	int byte_found = 0; /* whether a != 0xff byte has been found */
	const unsigned char *pos;
	unsigned long max_loop_count, i;

	/* scan bits until we hit a byte boundary */
	while ((bitpos & 0x7) != 0 && count > 0) {
		if (!ext2fs_test_bit64(bitpos, bp->bitarray)) {
			*out = bitpos + bitmap->start;
			return 0;
		}
		bitpos++;
		count--;
	}

	if (!count)
		return ENOENT;

	pos = ((unsigned char *)bp->bitarray) + (bitpos >> 3);
	/* scan bytes until 8-byte (64-bit) aligned */
	while (count >= 8 && (((uintptr_t)pos) & 0x07)) {
		if (*pos != 0xff) {
			byte_found = 1;
			break;
		}
		pos++;
		count -= 8;
		bitpos += 8;
	}

	if (!byte_found) {
		max_loop_count = count >> 6; /* 8-byte blocks */
		i = max_loop_count;
		while (i) {
			if (*((const __u64 *)pos) != ((__u64)-1))
				break;
			pos += 8;
			i--;
		}
		count -= 64 * (max_loop_count - i);
		bitpos += 64 * (max_loop_count - i);

		max_loop_count = count >> 3;
		i = max_loop_count;
		while (i) {
			if (*pos != 0xff) {
				byte_found = 1;
				break;
			}
			pos++;
			i--;
		}
		count -= 8 * (max_loop_count - i);
		bitpos += 8 * (max_loop_count - i);
	}

	/* Here either count < 8 or byte_found == 1. */
	while (count-- > 0) {
		if (!ext2fs_test_bit64(bitpos, bp->bitarray)) {
			*out = bitpos + bitmap->start;
			return 0;
		}
		bitpos++;
	}

	return ENOENT;
}