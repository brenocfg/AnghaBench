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
typedef  int i16 ;
struct TYPE_3__ {int accuracy_log; int* symbols; size_t* num_bits; size_t* new_state_base; } ;
typedef  TYPE_1__ FSE_dtable ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ALLOC () ; 
 int /*<<< orphan*/  CORRUPTION () ; 
 int /*<<< orphan*/  ERROR (char*) ; 
 int const FSE_MAX_ACCURACY_LOG ; 
 int const FSE_MAX_SYMBS ; 
 int const highest_set_bit (size_t) ; 
 void* malloc (size_t const) ; 

__attribute__((used)) static void FSE_init_dtable(FSE_dtable *const dtable,
                            const i16 *const norm_freqs, const int num_symbs,
                            const int accuracy_log) {
    if (accuracy_log > FSE_MAX_ACCURACY_LOG) {
        ERROR("FSE accuracy too large");
    }
    if (num_symbs > FSE_MAX_SYMBS) {
        ERROR("Too many symbols for FSE");
    }

    dtable->accuracy_log = accuracy_log;

    const size_t size = (size_t)1 << accuracy_log;
    dtable->symbols = malloc(size * sizeof(u8));
    dtable->num_bits = malloc(size * sizeof(u8));
    dtable->new_state_base = malloc(size * sizeof(u16));

    if (!dtable->symbols || !dtable->num_bits || !dtable->new_state_base) {
        BAD_ALLOC();
    }

    // Used to determine how many bits need to be read for each state,
    // and where the destination range should start
    // Needs to be u16 because max value is 2 * max number of symbols,
    // which can be larger than a byte can store
    u16 state_desc[FSE_MAX_SYMBS];

    // "Symbols are scanned in their natural order for "less than 1"
    // probabilities. Symbols with this probability are being attributed a
    // single cell, starting from the end of the table. These symbols define a
    // full state reset, reading Accuracy_Log bits."
    int high_threshold = size;
    for (int s = 0; s < num_symbs; s++) {
        // Scan for low probability symbols to put at the top
        if (norm_freqs[s] == -1) {
            dtable->symbols[--high_threshold] = s;
            state_desc[s] = 1;
        }
    }

    // "All remaining symbols are sorted in their natural order. Starting from
    // symbol 0 and table position 0, each symbol gets attributed as many cells
    // as its probability. Cell allocation is spreaded, not linear."
    // Place the rest in the table
    const u16 step = (size >> 1) + (size >> 3) + 3;
    const u16 mask = size - 1;
    u16 pos = 0;
    for (int s = 0; s < num_symbs; s++) {
        if (norm_freqs[s] <= 0) {
            continue;
        }

        state_desc[s] = norm_freqs[s];

        for (int i = 0; i < norm_freqs[s]; i++) {
            // Give `norm_freqs[s]` states to symbol s
            dtable->symbols[pos] = s;
            // "A position is skipped if already occupied, typically by a "less
            // than 1" probability symbol."
            do {
                pos = (pos + step) & mask;
            } while (pos >=
                     high_threshold);
            // Note: no other collision checking is necessary as `step` is
            // coprime to `size`, so the cycle will visit each position exactly
            // once
        }
    }
    if (pos != 0) {
        CORRUPTION();
    }

    // Now we can fill baseline and num bits
    for (size_t i = 0; i < size; i++) {
        u8 symbol = dtable->symbols[i];
        u16 next_state_desc = state_desc[symbol]++;
        // Fills in the table appropriately, next_state_desc increases by symbol
        // over time, decreasing number of bits
        dtable->num_bits[i] = (u8)(accuracy_log - highest_set_bit(next_state_desc));
        // Baseline increases until the bit threshold is passed, at which point
        // it resets to 0
        dtable->new_state_base[i] =
            ((u16)next_state_desc << dtable->num_bits[i]) - size;
    }
}