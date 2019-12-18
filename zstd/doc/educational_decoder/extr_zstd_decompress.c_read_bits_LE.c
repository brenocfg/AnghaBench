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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 

__attribute__((used)) static inline u64 read_bits_LE(const u8 *src, const int num_bits,
                               const size_t offset) {
    if (num_bits > 64) {
        ERROR("Attempt to read an invalid number of bits");
    }

    // Skip over bytes that aren't in range
    src += offset / 8;
    size_t bit_offset = offset % 8;
    u64 res = 0;

    int shift = 0;
    int left = num_bits;
    while (left > 0) {
        u64 mask = left >= 8 ? 0xff : (((u64)1 << left) - 1);
        // Read the next byte, shift it to account for the offset, and then mask
        // out the top part if we don't need all the bits
        res += (((u64)*src++ >> bit_offset) & mask) << shift;
        shift += 8 - bit_offset;
        left -= 8 - bit_offset;
        bit_offset = 0;
    }

    return res;
}