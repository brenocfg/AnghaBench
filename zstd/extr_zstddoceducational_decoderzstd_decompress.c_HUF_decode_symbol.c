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
typedef  size_t u8 ;
typedef  size_t u16 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_3__ {size_t* symbols; size_t* num_bits; size_t max_bits; } ;
typedef  TYPE_1__ HUF_dtable ;

/* Variables and functions */
 size_t STREAM_read_bits (size_t const* const,size_t const,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static inline u8 HUF_decode_symbol(const HUF_dtable *const dtable,
                                   u16 *const state, const u8 *const src,
                                   i64 *const offset) {
    // Look up the symbol and number of bits to read
    const u8 symb = dtable->symbols[*state];
    const u8 bits = dtable->num_bits[*state];
    const u16 rest = STREAM_read_bits(src, bits, offset);
    // Shift `bits` bits out of the state, keeping the low order bits that
    // weren't necessary to determine this symbol.  Then add in the new bits
    // read from the stream.
    *state = ((*state << bits) + rest) & (((u16)1 << dtable->max_bits) - 1);

    return symb;
}