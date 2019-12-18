#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int referred_to_segment_count; int flags; int /*<<< orphan*/  result; int /*<<< orphan*/ * referred_to_segments; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int /*<<< orphan*/  jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* jbig2_find_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Jbig2Segment *
jbig2_region_find_referred(Jbig2Ctx *ctx, Jbig2Segment *segment)
{
    const int nsegments = segment->referred_to_segment_count;
    Jbig2Segment *rsegment;
    int index;

    for (index = 0; index < nsegments; index++) {
        rsegment = jbig2_find_segment(ctx, segment->referred_to_segments[index]);
        if (rsegment == NULL) {
            jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "failed to find referred to segment %d", segment->referred_to_segments[index]);
            continue;
        }
        switch (rsegment->flags & 63) {
        case 4:                /* intermediate text region */
        case 20:               /* intermediate halftone region */
        case 36:               /* intermediate generic region */
        case 40:               /* intermediate generic refinement region */
            if (rsegment->result)
                return rsegment;
            break;
        default:               /* keep looking */
            break;
        }
    }
    /* no appropriate reference was found. */
    return NULL;
}