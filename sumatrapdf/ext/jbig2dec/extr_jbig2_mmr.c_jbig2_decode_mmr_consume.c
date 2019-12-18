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
struct TYPE_3__ {int word; int bit_index; int data_index; int size; int* data; } ;
typedef  TYPE_1__ Jbig2MmrCtx ;

/* Variables and functions */

__attribute__((used)) static void
jbig2_decode_mmr_consume(Jbig2MmrCtx *mmr, int n_bits)
{
    mmr->word <<= n_bits;
    mmr->bit_index += n_bits;
    while (mmr->bit_index >= 8) {
        mmr->bit_index -= 8;
        if (mmr->data_index + 4 < mmr->size)
            mmr->word |= (mmr->data[mmr->data_index + 4] << mmr->bit_index);
        mmr->data_index++;
    }
}