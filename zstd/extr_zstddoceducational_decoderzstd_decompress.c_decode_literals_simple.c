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
typedef  int /*<<< orphan*/  istream_t ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ALLOC () ; 
 int /*<<< orphan*/  CORRUPTION () ; 
 int /*<<< orphan*/  IMPOSSIBLE () ; 
 int /*<<< orphan*/ * IO_get_read_ptr (int /*<<< orphan*/ * const,int) ; 
 size_t IO_read_bits (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  IO_rewind_bits (int /*<<< orphan*/ * const,int) ; 
 size_t MAX_LITERALS_SIZE ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/  const,size_t) ; 

__attribute__((used)) static size_t decode_literals_simple(istream_t *const in, u8 **const literals,
                                     const int block_type,
                                     const int size_format) {
    size_t size;
    switch (size_format) {
    // These cases are in the form ?0
    // In this case, the ? bit is actually part of the size field
    case 0:
    case 2:
        // "Size_Format uses 1 bit. Regenerated_Size uses 5 bits (0-31)."
        IO_rewind_bits(in, 1);
        size = IO_read_bits(in, 5);
        break;
    case 1:
        // "Size_Format uses 2 bits. Regenerated_Size uses 12 bits (0-4095)."
        size = IO_read_bits(in, 12);
        break;
    case 3:
        // "Size_Format uses 2 bits. Regenerated_Size uses 20 bits (0-1048575)."
        size = IO_read_bits(in, 20);
        break;
    default:
        // Size format is in range 0-3
        IMPOSSIBLE();
    }

    if (size > MAX_LITERALS_SIZE) {
        CORRUPTION();
    }

    *literals = malloc(size);
    if (!*literals) {
        BAD_ALLOC();
    }

    switch (block_type) {
    case 0: {
        // "Raw_Literals_Block - Literals are stored uncompressed."
        const u8 *const read_ptr = IO_get_read_ptr(in, size);
        memcpy(*literals, read_ptr, size);
        break;
    }
    case 1: {
        // "RLE_Literals_Block - Literals consist of a single byte value repeated N times."
        const u8 *const read_ptr = IO_get_read_ptr(in, 1);
        memset(*literals, read_ptr[0], size);
        break;
    }
    default:
        IMPOSSIBLE();
    }

    return size;
}