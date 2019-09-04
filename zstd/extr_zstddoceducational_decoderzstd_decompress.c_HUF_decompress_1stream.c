#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  ostream_t ;
typedef  int /*<<< orphan*/  istream_t ;
typedef  size_t i64 ;
struct TYPE_5__ {size_t max_bits; } ;
typedef  TYPE_1__ HUF_dtable ;

/* Variables and functions */
 int /*<<< orphan*/  CORRUPTION () ; 
 int /*<<< orphan*/  HUF_decode_symbol (TYPE_1__ const* const,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,size_t*) ; 
 int /*<<< orphan*/  HUF_init_state (TYPE_1__ const* const,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,size_t*) ; 
 int /*<<< orphan*/  INP_SIZE () ; 
 int /*<<< orphan*/ * IO_get_read_ptr (int /*<<< orphan*/ * const,size_t const) ; 
 size_t IO_istream_len (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  IO_write_byte (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int highest_set_bit (int /*<<< orphan*/  const) ; 

__attribute__((used)) static size_t HUF_decompress_1stream(const HUF_dtable *const dtable,
                                     ostream_t *const out,
                                     istream_t *const in) {
    const size_t len = IO_istream_len(in);
    if (len == 0) {
        INP_SIZE();
    }
    const u8 *const src = IO_get_read_ptr(in, len);

    // "Each bitstream must be read backward, that is starting from the end down
    // to the beginning. Therefore it's necessary to know the size of each
    // bitstream.
    //
    // It's also necessary to know exactly which bit is the latest. This is
    // detected by a final bit flag : the highest bit of latest byte is a
    // final-bit-flag. Consequently, a last byte of 0 is not possible. And the
    // final-bit-flag itself is not part of the useful bitstream. Hence, the
    // last byte contains between 0 and 7 useful bits."
    const int padding = 8 - highest_set_bit(src[len - 1]);

    // Offset starts at the end because HUF streams are read backwards
    i64 bit_offset = len * 8 - padding;
    u16 state;

    HUF_init_state(dtable, &state, src, &bit_offset);

    size_t symbols_written = 0;
    while (bit_offset > -dtable->max_bits) {
        // Iterate over the stream, decoding one symbol at a time
        IO_write_byte(out, HUF_decode_symbol(dtable, &state, src, &bit_offset));
        symbols_written++;
    }
    // "The process continues up to reading the required number of symbols per
    // stream. If a bitstream is not entirely and exactly consumed, hence
    // reaching exactly its beginning position with all bits consumed, the
    // decoding process is considered faulty."

    // When all symbols have been decoded, the final state value shouldn't have
    // any data from the stream, so it should have "read" dtable->max_bits from
    // before the start of `src`
    // Therefore `offset`, the edge to start reading new bits at, should be
    // dtable->max_bits before the start of the stream
    if (bit_offset != -dtable->max_bits) {
        CORRUPTION();
    }

    return symbols_written;
}