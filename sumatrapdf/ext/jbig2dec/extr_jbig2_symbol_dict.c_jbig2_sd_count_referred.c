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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int referred_to_segment_count; int flags; scalar_t__ result; int /*<<< orphan*/ * referred_to_segments; } ;
struct TYPE_5__ {scalar_t__ n_symbols; int /*<<< orphan*/ ** glyphs; } ;
typedef  TYPE_1__ Jbig2SymbolDict ;
typedef  TYPE_2__ Jbig2Segment ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;

/* Variables and functions */
 TYPE_2__* jbig2_find_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uint32_t
jbig2_sd_count_referred(Jbig2Ctx *ctx, Jbig2Segment *segment)
{
    int index;
    Jbig2Segment *rsegment;
    uint32_t n_dicts = 0;

    for (index = 0; index < segment->referred_to_segment_count; index++) {
        rsegment = jbig2_find_segment(ctx, segment->referred_to_segments[index]);
        if (rsegment && ((rsegment->flags & 63) == 0) &&
            rsegment->result && (((Jbig2SymbolDict *) rsegment->result)->n_symbols > 0) && ((*((Jbig2SymbolDict *) rsegment->result)->glyphs) != NULL))
            n_dicts++;
    }

    return (n_dicts);
}