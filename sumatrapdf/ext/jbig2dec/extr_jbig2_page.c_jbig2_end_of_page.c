#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {size_t current_page; TYPE_1__* pages; } ;
struct TYPE_9__ {scalar_t__ page_association; int /*<<< orphan*/  number; } ;
struct TYPE_8__ {scalar_t__ number; int /*<<< orphan*/  image; } ;
typedef  TYPE_2__ Jbig2Segment ;
typedef  TYPE_3__ Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_INFO ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int jbig2_complete_page (TYPE_3__*) ; 
 int jbig2_error (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int jbig2_image_write_pbm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

int
jbig2_end_of_page(Jbig2Ctx *ctx, Jbig2Segment *segment, const uint8_t *segment_data)
{
    uint32_t page_number = ctx->pages[ctx->current_page].number;
    int code;

    if (segment->page_association != page_number) {
        jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number,
                    "end of page marker for page %d doesn't match current page number %d", segment->page_association, page_number);
    }

    jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "end of page %d", page_number);

    code = jbig2_complete_page(ctx);
    if (code < 0)
        return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "failed to complete page");

#ifdef OUTPUT_PBM
    code = jbig2_image_write_pbm(ctx->pages[ctx->current_page].image, stdout);
    if (code < 0)
        return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "failed to write page image");
#endif

    return 0;
}