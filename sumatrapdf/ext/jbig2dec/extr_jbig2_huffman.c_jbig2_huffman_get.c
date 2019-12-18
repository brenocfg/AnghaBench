#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int byte ;
struct TYPE_8__ {int RANGELOW; TYPE_2__* ext_table; } ;
struct TYPE_11__ {int flags; int PREFLEN; int RANGELEN; TYPE_1__ u; } ;
struct TYPE_10__ {int offset_bits; int this_word; scalar_t__ offset_limit; scalar_t__ offset; int next_word; int /*<<< orphan*/  ctx; } ;
struct TYPE_9__ {int log_table_size; TYPE_4__* entries; } ;
typedef  TYPE_2__ Jbig2HuffmanTable ;
typedef  TYPE_3__ Jbig2HuffmanState ;
typedef  TYPE_4__ Jbig2HuffmanEntry ;

/* Variables and functions */
 int JBIG2_HUFFMAN_FLAGS_ISEXT ; 
 int JBIG2_HUFFMAN_FLAGS_ISLOW ; 
 int JBIG2_HUFFMAN_FLAGS_ISOOB ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int huff_get_next_word (TYPE_3__*,scalar_t__,int*) ; 
 int jbig2_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 

int32_t
jbig2_huffman_get(Jbig2HuffmanState *hs, const Jbig2HuffmanTable *table, bool *oob)
{
    Jbig2HuffmanEntry *entry;
    byte flags;
    int offset_bits = hs->offset_bits;
    uint32_t this_word = hs->this_word;
    uint32_t next_word;
    int RANGELEN;
    int32_t result;

    if (hs->offset_limit && hs->offset >= hs->offset_limit) {
        if (oob)
            *oob = -1;
        return jbig2_error(hs->ctx, JBIG2_SEVERITY_FATAL, -1, "end of Jbig2WordStream reached at offset %d", hs->offset);
    }

    for (;;) {
        int log_table_size = table->log_table_size;
        int PREFLEN;
        int code;

        /* SumatraPDF: shifting by the size of the operand is undefined */
        entry = &table->entries[log_table_size > 0 ? this_word >> (32 - log_table_size) : 0];
        flags = entry->flags;
        PREFLEN = entry->PREFLEN;
        if (flags == (byte) -1 && PREFLEN == (byte) -1 && entry->u.RANGELOW == -1) {
            if (oob)
                *oob = -1;
            return jbig2_error(hs->ctx, JBIG2_SEVERITY_FATAL, -1, "encountered unpopulated huffman table entry");
        }

        next_word = hs->next_word;
        offset_bits += PREFLEN;
        if (offset_bits >= 32) {
            this_word = next_word;
            hs->offset += 4;
            code = huff_get_next_word(hs, hs->offset + 4, &next_word);
            if (code < 0) {
                return jbig2_error(hs->ctx, JBIG2_SEVERITY_WARNING, -1, "failed to get next huffman word");
            }
            offset_bits -= 32;
            hs->next_word = next_word;
            PREFLEN = offset_bits;
        }
        if (PREFLEN)
            this_word = (this_word << PREFLEN) | (next_word >> (32 - offset_bits));
        if (flags & JBIG2_HUFFMAN_FLAGS_ISEXT) {
            table = entry->u.ext_table;
        } else
            break;
    }
    result = entry->u.RANGELOW;
    RANGELEN = entry->RANGELEN;
    if (RANGELEN > 0) {
        int32_t HTOFFSET;
        int code;

        HTOFFSET = this_word >> (32 - RANGELEN);
        if (flags & JBIG2_HUFFMAN_FLAGS_ISLOW)
            result -= HTOFFSET;
        else
            result += HTOFFSET;

        offset_bits += RANGELEN;
        if (offset_bits >= 32) {
            this_word = next_word;
            hs->offset += 4;
            code = huff_get_next_word(hs, hs->offset + 4, &next_word);
            if (code < 0) {
                return jbig2_error(hs->ctx, JBIG2_SEVERITY_WARNING, -1, "failed to get next huffman word");
            }
            offset_bits -= 32;
            hs->next_word = next_word;
            RANGELEN = offset_bits;
        }
        if (RANGELEN)
            this_word = (this_word << RANGELEN) | (next_word >> (32 - offset_bits));
    }

    hs->this_word = this_word;
    hs->offset_bits = offset_bits;

    if (oob != NULL)
        *oob = (flags & JBIG2_HUFFMAN_FLAGS_ISOOB);

    return result;
}