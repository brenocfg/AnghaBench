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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  ostream_t ;
typedef  int /*<<< orphan*/  istream_t ;
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  FSE_dtable ;

/* Variables and functions */
 int /*<<< orphan*/  FSE_decode_symbol (int /*<<< orphan*/  const* const,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,scalar_t__*) ; 
 int /*<<< orphan*/  FSE_init_state (int /*<<< orphan*/  const* const,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,scalar_t__*) ; 
 int /*<<< orphan*/  FSE_peek_symbol (int /*<<< orphan*/  const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_SIZE () ; 
 int /*<<< orphan*/ * IO_get_read_ptr (int /*<<< orphan*/ * const,size_t const) ; 
 size_t IO_istream_len (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  IO_write_byte (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int highest_set_bit (int /*<<< orphan*/  const) ; 

__attribute__((used)) static size_t FSE_decompress_interleaved2(const FSE_dtable *const dtable,
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
    i64 offset = len * 8 - padding;

    u16 state1, state2;
    // "The first state (State1) encodes the even indexed symbols, and the
    // second (State2) encodes the odd indexes. State1 is initialized first, and
    // then State2, and they take turns decoding a single symbol and updating
    // their state."
    FSE_init_state(dtable, &state1, src, &offset);
    FSE_init_state(dtable, &state2, src, &offset);

    // Decode until we overflow the stream
    // Since we decode in reverse order, overflowing the stream is offset going
    // negative
    size_t symbols_written = 0;
    while (1) {
        // "The number of symbols to decode is determined by tracking bitStream
        // overflow condition: If updating state after decoding a symbol would
        // require more bits than remain in the stream, it is assumed the extra
        // bits are 0. Then, the symbols for each of the final states are
        // decoded and the process is complete."
        IO_write_byte(out, FSE_decode_symbol(dtable, &state1, src, &offset));
        symbols_written++;
        if (offset < 0) {
            // There's still a symbol to decode in state2
            IO_write_byte(out, FSE_peek_symbol(dtable, state2));
            symbols_written++;
            break;
        }

        IO_write_byte(out, FSE_decode_symbol(dtable, &state2, src, &offset));
        symbols_written++;
        if (offset < 0) {
            // There's still a symbol to decode in state1
            IO_write_byte(out, FSE_peek_symbol(dtable, state1));
            symbols_written++;
            break;
        }
    }

    return symbols_written;
}