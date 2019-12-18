#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int /*<<< orphan*/  ml_state; int /*<<< orphan*/  ml_table; int /*<<< orphan*/  of_state; int /*<<< orphan*/  of_table; int /*<<< orphan*/  ll_state; int /*<<< orphan*/  ll_table; } ;
typedef  TYPE_1__ sequence_states_t ;
typedef  int /*<<< orphan*/  sequence_command_t ;
typedef  int /*<<< orphan*/  istream_t ;
typedef  scalar_t__ i64 ;
struct TYPE_6__ {int /*<<< orphan*/  ml_dtable; int /*<<< orphan*/  of_dtable; int /*<<< orphan*/  ll_dtable; } ;
typedef  TYPE_2__ frame_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORRUPTION () ; 
 int /*<<< orphan*/  FSE_init_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const* const,scalar_t__*) ; 
 int* IO_get_read_ptr (int /*<<< orphan*/ *,size_t const) ; 
 size_t IO_istream_len (int /*<<< orphan*/ *) ; 
 int IO_read_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_seq_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  decode_sequence (TYPE_1__*,int const* const,scalar_t__*) ; 
 int highest_set_bit (int const) ; 
 int /*<<< orphan*/  seq_literal_length ; 
 int /*<<< orphan*/  seq_match_length ; 
 int /*<<< orphan*/  seq_offset ; 

__attribute__((used)) static void decompress_sequences(frame_context_t *const ctx, istream_t *in,
                                 sequence_command_t *const sequences,
                                 const size_t num_sequences) {
    // "The Sequences_Section regroup all symbols required to decode commands.
    // There are 3 symbol types : literals lengths, offsets and match lengths.
    // They are encoded together, interleaved, in a single bitstream."

    // "Symbol compression modes
    //
    // This is a single byte, defining the compression mode of each symbol
    // type."
    //
    // Bit number : Field name
    // 7-6        : Literals_Lengths_Mode
    // 5-4        : Offsets_Mode
    // 3-2        : Match_Lengths_Mode
    // 1-0        : Reserved
    u8 compression_modes = IO_read_bits(in, 8);

    if ((compression_modes & 3) != 0) {
        // Reserved bits set
        CORRUPTION();
    }

    // "Following the header, up to 3 distribution tables can be described. When
    // present, they are in this order :
    //
    // Literals lengths
    // Offsets
    // Match Lengths"
    // Update the tables we have stored in the context
    decode_seq_table(&ctx->ll_dtable, in, seq_literal_length,
                     (compression_modes >> 6) & 3);

    decode_seq_table(&ctx->of_dtable, in, seq_offset,
                     (compression_modes >> 4) & 3);

    decode_seq_table(&ctx->ml_dtable, in, seq_match_length,
                     (compression_modes >> 2) & 3);


    sequence_states_t states;

    // Initialize the decoding tables
    {
        states.ll_table = ctx->ll_dtable;
        states.of_table = ctx->of_dtable;
        states.ml_table = ctx->ml_dtable;
    }

    const size_t len = IO_istream_len(in);
    const u8 *const src = IO_get_read_ptr(in, len);

    // "After writing the last bit containing information, the compressor writes
    // a single 1-bit and then fills the byte with 0-7 0 bits of padding."
    const int padding = 8 - highest_set_bit(src[len - 1]);
    // The offset starts at the end because FSE streams are read backwards
    i64 bit_offset = (i64)(len * 8 - (size_t)padding);

    // "The bitstream starts with initial state values, each using the required
    // number of bits in their respective accuracy, decoded previously from
    // their normalized distribution.
    //
    // It starts by Literals_Length_State, followed by Offset_State, and finally
    // Match_Length_State."
    FSE_init_state(&states.ll_table, &states.ll_state, src, &bit_offset);
    FSE_init_state(&states.of_table, &states.of_state, src, &bit_offset);
    FSE_init_state(&states.ml_table, &states.ml_state, src, &bit_offset);

    for (size_t i = 0; i < num_sequences; i++) {
        // Decode sequences one by one
        sequences[i] = decode_sequence(&states, src, &bit_offset);
    }

    if (bit_offset != 0) {
        CORRUPTION();
    }
}