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
typedef  int u16 ;
typedef  int /*<<< orphan*/  istream_t ;
typedef  scalar_t__ i32 ;
typedef  scalar_t__ i16 ;
typedef  int /*<<< orphan*/  FSE_dtable ;

/* Variables and functions */
 int /*<<< orphan*/  CORRUPTION () ; 
 int /*<<< orphan*/  ERROR (char*) ; 
 int const FSE_MAX_ACCURACY_LOG ; 
 int FSE_MAX_SYMBS ; 
 int /*<<< orphan*/  FSE_init_dtable (int /*<<< orphan*/ * const,scalar_t__*,int,int const) ; 
 int /*<<< orphan*/  IO_align_stream (int /*<<< orphan*/ * const) ; 
 int IO_read_bits (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  IO_rewind_bits (int /*<<< orphan*/ * const,int) ; 
 int highest_set_bit (scalar_t__) ; 

__attribute__((used)) static void FSE_decode_header(FSE_dtable *const dtable, istream_t *const in,
                                const int max_accuracy_log) {
    // "An FSE distribution table describes the probabilities of all symbols
    // from 0 to the last present one (included) on a normalized scale of 1 <<
    // Accuracy_Log .
    //
    // It's a bitstream which is read forward, in little-endian fashion. It's
    // not necessary to know its exact size, since it will be discovered and
    // reported by the decoding process.
    if (max_accuracy_log > FSE_MAX_ACCURACY_LOG) {
        ERROR("FSE accuracy too large");
    }

    // The bitstream starts by reporting on which scale it operates.
    // Accuracy_Log = low4bits + 5. Note that maximum Accuracy_Log for literal
    // and match lengths is 9, and for offsets is 8. Higher values are
    // considered errors."
    const int accuracy_log = 5 + IO_read_bits(in, 4);
    if (accuracy_log > max_accuracy_log) {
        ERROR("FSE accuracy too large");
    }

    // "Then follows each symbol value, from 0 to last present one. The number
    // of bits used by each field is variable. It depends on :
    //
    // Remaining probabilities + 1 : example : Presuming an Accuracy_Log of 8,
    // and presuming 100 probabilities points have already been distributed, the
    // decoder may read any value from 0 to 255 - 100 + 1 == 156 (inclusive).
    // Therefore, it must read log2sup(156) == 8 bits.
    //
    // Value decoded : small values use 1 less bit : example : Presuming values
    // from 0 to 156 (inclusive) are possible, 255-156 = 99 values are remaining
    // in an 8-bits field. They are used this way : first 99 values (hence from
    // 0 to 98) use only 7 bits, values from 99 to 156 use 8 bits. "

    i32 remaining = 1 << accuracy_log;
    i16 frequencies[FSE_MAX_SYMBS];

    int symb = 0;
    while (remaining > 0 && symb < FSE_MAX_SYMBS) {
        // Log of the number of possible values we could read
        int bits = highest_set_bit(remaining + 1) + 1;

        u16 val = IO_read_bits(in, bits);

        // Try to mask out the lower bits to see if it qualifies for the "small
        // value" threshold
        const u16 lower_mask = ((u16)1 << (bits - 1)) - 1;
        const u16 threshold = ((u16)1 << bits) - 1 - (remaining + 1);

        if ((val & lower_mask) < threshold) {
            IO_rewind_bits(in, 1);
            val = val & lower_mask;
        } else if (val > lower_mask) {
            val = val - threshold;
        }

        // "Probability is obtained from Value decoded by following formula :
        // Proba = value - 1"
        const i16 proba = (i16)val - 1;

        // "It means value 0 becomes negative probability -1. -1 is a special
        // probability, which means "less than 1". Its effect on distribution
        // table is described in next paragraph. For the purpose of calculating
        // cumulated distribution, it counts as one."
        remaining -= proba < 0 ? -proba : proba;

        frequencies[symb] = proba;
        symb++;

        // "When a symbol has a probability of zero, it is followed by a 2-bits
        // repeat flag. This repeat flag tells how many probabilities of zeroes
        // follow the current one. It provides a number ranging from 0 to 3. If
        // it is a 3, another 2-bits repeat flag follows, and so on."
        if (proba == 0) {
            // Read the next two bits to see how many more 0s
            int repeat = IO_read_bits(in, 2);

            while (1) {
                for (int i = 0; i < repeat && symb < FSE_MAX_SYMBS; i++) {
                    frequencies[symb++] = 0;
                }
                if (repeat == 3) {
                    repeat = IO_read_bits(in, 2);
                } else {
                    break;
                }
            }
        }
    }
    IO_align_stream(in);

    // "When last symbol reaches cumulated total of 1 << Accuracy_Log, decoding
    // is complete. If the last symbol makes cumulated total go above 1 <<
    // Accuracy_Log, distribution is considered corrupted."
    if (remaining != 0 || symb >= FSE_MAX_SYMBS) {
        CORRUPTION();
    }

    // Initialize the decoding table using the determined weights
    FSE_init_dtable(dtable, frequencies, symb, accuracy_log);
}