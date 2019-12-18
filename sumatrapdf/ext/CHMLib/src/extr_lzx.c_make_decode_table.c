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
typedef  int UWORD ;
typedef  int ULONG ;
typedef  int UBYTE ;

/* Variables and functions */

__attribute__((used)) static int make_decode_table(ULONG nsyms, ULONG nbits, UBYTE *length, UWORD *table) {
    register UWORD sym;
    register ULONG leaf;
    register UBYTE bit_num = 1;
    ULONG fill;
    ULONG pos         = 0; /* the current position in the decode table */
    ULONG table_mask  = 1 << nbits;
    ULONG bit_mask    = table_mask >> 1; /* don't do 0 length codes */
    ULONG next_symbol = bit_mask; /* base of allocation for long codes */

    /* fill entries for codes short enough for a direct mapping */
    while (bit_num <= nbits) {
        for (sym = 0; sym < nsyms; sym++) {
            if (length[sym] == bit_num) {
                leaf = pos;

                if((pos += bit_mask) > table_mask) return 1; /* table overrun */

                /* fill all possible lookups of this symbol with the symbol itself */
                fill = bit_mask;
                while (fill-- > 0) table[leaf++] = sym;
            }
        }
        bit_mask >>= 1;
        bit_num++;
    }

    /* if there are any codes longer than nbits */
    if (pos != table_mask) {
        /* clear the remainder of the table */
        for (sym = pos; sym < table_mask; sym++) table[sym] = 0;

        /* give ourselves room for codes to grow by up to 16 more bits */
        pos <<= 16;
        table_mask <<= 16;
        bit_mask = 1 << 15;

        while (bit_num <= 16) {
            for (sym = 0; sym < nsyms; sym++) {
                if (length[sym] == bit_num) {
                    leaf = pos >> 16;
                    for (fill = 0; fill < bit_num - nbits; fill++) {
                        /* if this path hasn't been taken yet, 'allocate' two entries */
                        if (table[leaf] == 0) {
                            table[(next_symbol << 1)] = 0;
                            table[(next_symbol << 1) + 1] = 0;
                            table[leaf] = next_symbol++;
                        }
                        /* follow the path and select either left or right for next bit */
                        leaf = table[leaf] << 1;
                        if ((pos >> (15-fill)) & 1) leaf++;
                    }
                    table[leaf] = sym;

                    if ((pos += bit_mask) > table_mask) return 1; /* table overflow */
                }
            }
            bit_mask >>= 1;
            bit_num++;
        }
    }

    /* full table? */
    if (pos == table_mask) return 0;

    /* either erroneous table, or all elements are 0 - let's find out. */
    for (sym = 0; sym < nsyms; sym++) if (length[sym]) return 1;
    return 0;
}