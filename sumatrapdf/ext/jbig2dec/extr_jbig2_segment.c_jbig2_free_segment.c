#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  allocator; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/ * result; struct TYPE_10__* referred_to_segments; } ;
typedef  int /*<<< orphan*/  Jbig2SymbolDict ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  int /*<<< orphan*/  Jbig2PatternDict ;
typedef  int /*<<< orphan*/  Jbig2Image ;
typedef  int /*<<< orphan*/  Jbig2HuffmanParams ;
typedef  TYPE_2__ Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  jbig2_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  jbig2_hd_release (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbig2_image_release (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbig2_sd_release (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbig2_table_free (TYPE_2__*,int /*<<< orphan*/ *) ; 

void
jbig2_free_segment(Jbig2Ctx *ctx, Jbig2Segment *segment)
{
    if (segment == NULL)
        return;

    jbig2_free(ctx->allocator, segment->referred_to_segments);
    /* todo: we need either some separate fields or
       a more complex result object rather than this
       brittle special casing */
    switch (segment->flags & 63) {
    case 0:                    /* symbol dictionary */
        if (segment->result != NULL)
            jbig2_sd_release(ctx, (Jbig2SymbolDict *) segment->result);
        break;
    case 4:                    /* intermediate text region */
    case 40:                   /* intermediate refinement region */
        if (segment->result != NULL)
            jbig2_image_release(ctx, (Jbig2Image *) segment->result);
        break;
    case 16:                   /* pattern dictionary */
        if (segment->result != NULL)
            jbig2_hd_release(ctx, (Jbig2PatternDict *) segment->result);
        break;
    case 53:                   /* user-supplied huffman table */
        if (segment->result != NULL)
            jbig2_table_free(ctx, (Jbig2HuffmanParams *) segment->result);
        break;
    default:
        /* anything else is probably an undefined pointer */
        break;
    }
    jbig2_free(ctx->allocator, segment);
}