#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t offset_bits; int this_word; int next_word; int /*<<< orphan*/  ctx; scalar_t__ offset; } ;
typedef  TYPE_1__ Jbig2HuffmanState ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int huff_get_next_word (TYPE_1__*,scalar_t__,int*) ; 
 int jbig2_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
jbig2_huffman_advance(Jbig2HuffmanState *hs, size_t advance)
{
    int code;
    hs->offset += advance & ~3;
    hs->offset_bits += (advance & 3) << 3;
    if (hs->offset_bits >= 32) {
        hs->offset += 4;
        hs->offset_bits -= 32;
    }
    code = huff_get_next_word(hs, hs->offset, &hs->this_word);
    if (code < 0) {
        return jbig2_error(hs->ctx, JBIG2_SEVERITY_WARNING, -1, "failed to get first huffman word after advancing");
    }
    code = huff_get_next_word(hs, hs->offset + 4, &hs->next_word);
    if (code < 0) {
        return jbig2_error(hs->ctx, JBIG2_SEVERITY_WARNING, -1, "failed to get second huffman word after advancing");
    }
    if (hs->offset_bits > 0)
        hs->this_word = (hs->this_word << hs->offset_bits) | (hs->next_word >> (32 - hs->offset_bits));
    return 0;
}