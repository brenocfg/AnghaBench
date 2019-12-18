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
struct TYPE_10__ {size_t segment_index; size_t n_segments; int buf_wr_ix; int buf_rd_ix; int buf; size_t current_page; TYPE_1__* pages; TYPE_2__** segments; } ;
struct TYPE_9__ {int data_length; int number; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * image; } ;
typedef  TYPE_2__ Jbig2Segment ;
typedef  TYPE_3__ Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_PAGE_COMPLETE ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int jbig2_error (TYPE_3__*,int /*<<< orphan*/ ,int,char*) ; 
 int jbig2_parse_segment (TYPE_3__*,TYPE_2__*,int) ; 

int
jbig2_complete_page(Jbig2Ctx *ctx)
{
    int code;

    /* check for unfinished segments */
    if (ctx->segment_index != ctx->n_segments) {
        Jbig2Segment *segment = ctx->segments[ctx->segment_index];

        /* Some versions of Xerox Workcentre generate PDF files
           with the segment data length field of the last segment
           set to -1. Try to cope with this here. */
        if ((segment->data_length & 0xffffffff) == 0xffffffff) {
            jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "file has an invalid segment data length; trying to decode using the available data");
            segment->data_length = ctx->buf_wr_ix - ctx->buf_rd_ix;
            code = jbig2_parse_segment(ctx, segment, ctx->buf + ctx->buf_rd_ix);
            ctx->buf_rd_ix += segment->data_length;
            ctx->segment_index++;
            if (code < 0) {
                return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "failed to parse segment");
            }
        }
    }

    /* ensure image exists before marking page as complete */
    if (ctx->pages[ctx->current_page].image == NULL) {
        return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "page has no image, cannot be completed");
    }

    ctx->pages[ctx->current_page].state = JBIG2_PAGE_COMPLETE;
    return 0;
}