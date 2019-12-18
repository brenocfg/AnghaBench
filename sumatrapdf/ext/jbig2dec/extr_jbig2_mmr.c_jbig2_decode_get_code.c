#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int val; int n_bits; } ;
typedef  TYPE_1__ mmr_table_node ;
struct TYPE_7__ {int word; } ;
typedef  TYPE_2__ Jbig2MmrCtx ;

/* Variables and functions */
 int /*<<< orphan*/  jbig2_decode_mmr_consume (TYPE_2__*,int) ; 

__attribute__((used)) static int
jbig2_decode_get_code(Jbig2MmrCtx *mmr, const mmr_table_node *table, int initial_bits)
{
    uint32_t word = mmr->word;
    int table_ix = word >> (32 - initial_bits);
    int val = table[table_ix].val;
    int n_bits = table[table_ix].n_bits;

    if (n_bits > initial_bits) {
        int mask = (1 << (32 - initial_bits)) - 1;

        table_ix = val + ((word & mask) >> (32 - n_bits));
        val = table[table_ix].val;
        n_bits = initial_bits + table[table_ix].n_bits;
    }

    jbig2_decode_mmr_consume(mmr, n_bits);

    return val;
}