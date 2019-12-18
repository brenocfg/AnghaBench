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
struct TYPE_4__ {int referred_to_segment_count; int flags; scalar_t__ result; int /*<<< orphan*/ * referred_to_segments; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  int /*<<< orphan*/  Jbig2PatternDict ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;

/* Variables and functions */
 TYPE_1__* jbig2_find_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Jbig2PatternDict *
jbig2_decode_ht_region_get_hpats(Jbig2Ctx *ctx, Jbig2Segment *segment)
{
    int index = 0;
    Jbig2PatternDict *pattern_dict = NULL;
    Jbig2Segment *rsegment = NULL;

    /* loop through all referred segments */
    while (!pattern_dict && segment->referred_to_segment_count > index) {
        rsegment = jbig2_find_segment(ctx, segment->referred_to_segments[index]);
        if (rsegment) {
            /* segment type is pattern dictionary and result is not empty */
            if ((rsegment->flags & 0x3f) == 16 && rsegment->result) {
                pattern_dict = (Jbig2PatternDict *) rsegment->result;
                return pattern_dict;
            }
        }
        index++;
    }
    return pattern_dict;
}