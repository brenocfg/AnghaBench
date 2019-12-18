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
struct TYPE_4__ {int referred_to_segment_count; int flags; int /*<<< orphan*/  number; scalar_t__ result; int /*<<< orphan*/ * referred_to_segments; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  int /*<<< orphan*/  Jbig2HuffmanParams ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int /*<<< orphan*/  jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* jbig2_find_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const Jbig2HuffmanParams *
jbig2_find_table(Jbig2Ctx *ctx, Jbig2Segment *segment, int index)
{
    int i, table_index = 0;

    for (i = 0; i < segment->referred_to_segment_count; i++) {
        const Jbig2Segment *const rsegment = jbig2_find_segment(ctx, segment->referred_to_segments[i]);

        if (rsegment && (rsegment->flags & 63) == 53) {
            if (table_index == index)
                return (const Jbig2HuffmanParams *)rsegment->result;
            ++table_index;
        }
    }

    jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "huffman table not found (%d)", index);
    return NULL;
}