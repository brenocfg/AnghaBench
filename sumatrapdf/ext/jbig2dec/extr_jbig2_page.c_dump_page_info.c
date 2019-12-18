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
struct TYPE_6__ {scalar_t__ x_resolution; scalar_t__ y_resolution; int /*<<< orphan*/  stripe_size; scalar_t__ striped; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  number; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ Jbig2Segment ;
typedef  TYPE_2__ Jbig2Page ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_INFO ; 
 int /*<<< orphan*/  jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
dump_page_info(Jbig2Ctx *ctx, Jbig2Segment *segment, Jbig2Page *page)
{
    if (page->x_resolution == 0) {
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "page %d image is %dx%d (unknown res)", page->number, page->width, page->height);
    } else if (page->x_resolution == page->y_resolution) {
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "page %d image is %dx%d (%d ppm)", page->number, page->width, page->height, page->x_resolution);
    } else {
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number,
                    "page %d image is %dx%d (%dx%d ppm)", page->number, page->width, page->height, page->x_resolution, page->y_resolution);
    }
    if (page->striped) {
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "\tmaximum stripe size: %d", page->stripe_size);
    }
}