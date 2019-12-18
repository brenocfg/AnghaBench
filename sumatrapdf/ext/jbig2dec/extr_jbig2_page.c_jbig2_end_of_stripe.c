#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {size_t current_page; TYPE_2__* pages; } ;
struct TYPE_8__ {scalar_t__ end_row; } ;
struct TYPE_7__ {int data_length; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  TYPE_2__ Jbig2Page ;
typedef  TYPE_3__ Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_INFO ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int jbig2_error (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ jbig2_get_uint32 (int /*<<< orphan*/  const*) ; 

int
jbig2_end_of_stripe(Jbig2Ctx *ctx, Jbig2Segment *segment, const uint8_t *segment_data)
{
    Jbig2Page *page = &ctx->pages[ctx->current_page];
    uint32_t end_row;

    if (segment->data_length < 4)
        return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "segment too short");
    end_row = jbig2_get_uint32(segment_data);
    if (end_row < page->end_row) {
        jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number,
                    "end of stripe segment with non-positive end row advance (new end row %d vs current end row %d)", end_row, page->end_row);
    } else {
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "end of stripe: advancing end row from %u to %u", page->end_row, end_row);
    }

    page->end_row = end_row;

    return 0;
}