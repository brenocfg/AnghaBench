#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ext2fs_generic_bitmap_32 ;
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;
struct TYPE_2__ {char* bitmap; scalar_t__ start; } ;

/* Variables and functions */
 int ext2fs_mem_is_zero (char const*,size_t) ; 

__attribute__((used)) static int ext2fs_test_clear_generic_bitmap_range(ext2fs_generic_bitmap gen_bitmap,
						  unsigned int start,
						  unsigned int len)
{
	ext2fs_generic_bitmap_32 bitmap = (ext2fs_generic_bitmap_32) gen_bitmap;
	size_t start_byte, len_byte = len >> 3;
	unsigned int start_bit, len_bit = len % 8;
	int first_bit = 0;
	int last_bit  = 0;
	int mark_count = 0;
	int mark_bit = 0;
	int i;
	const char *ADDR = bitmap->bitmap;

	start -= bitmap->start;
	start_byte = start >> 3;
	start_bit = start % 8;

	if (start_bit != 0) {
		/*
		 * The compared start block number or start inode number
		 * is not the first bit in a byte.
		 */
		mark_count = 8 - start_bit;
		if (len < 8 - start_bit) {
			mark_count = (int)len;
			mark_bit = len + start_bit - 1;
		} else
			mark_bit = 7;

		for (i = mark_count; i > 0; i--, mark_bit--)
			first_bit |= 1 << mark_bit;

		/*
		 * Compare blocks or inodes in the first byte.
		 * If there is any marked bit, this function returns 0.
		 */
		if (first_bit & ADDR[start_byte])
			return 0;
		else if (len <= 8 - start_bit)
			return 1;

		start_byte++;
		len_bit = (len - mark_count) % 8;
		len_byte = (len - mark_count) >> 3;
	}

	/*
	 * The compared start block number or start inode number is
	 * the first bit in a byte.
	 */
	if (len_bit != 0) {
		/*
		 * The compared end block number or end inode number is
		 * not the last bit in a byte.
		 */
		for (mark_bit = len_bit - 1; mark_bit >= 0; mark_bit--)
			last_bit |= 1 << mark_bit;

		/*
		 * Compare blocks or inodes in the last byte.
		 * If there is any marked bit, this function returns 0.
		 */
		if (last_bit & ADDR[start_byte + len_byte])
			return 0;
		else if (len_byte == 0)
			return 1;
	}

	/* Check whether all bytes are 0 */
	return ext2fs_mem_is_zero(ADDR + start_byte, len_byte);
}