#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int max_page_index; TYPE_1__* pages; } ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  number; int /*<<< orphan*/ * image; } ;
typedef  int /*<<< orphan*/  Jbig2Image ;
typedef  TYPE_2__ Jbig2Ctx ;

/* Variables and functions */
 scalar_t__ JBIG2_PAGE_COMPLETE ; 
 scalar_t__ JBIG2_PAGE_RETURNED ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_DEBUG ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int /*<<< orphan*/  jbig2_error (TYPE_2__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jbig2_image_reference (TYPE_2__*,int /*<<< orphan*/ *) ; 

Jbig2Image *
jbig2_page_out(Jbig2Ctx *ctx)
{
    int index;

    /* search for a completed page */
    for (index = 0; index < ctx->max_page_index; index++) {
        if (ctx->pages[index].state == JBIG2_PAGE_COMPLETE) {
            Jbig2Image *img = ctx->pages[index].image;
            uint32_t page_number = ctx->pages[index].number;

            if (img == NULL) {
                jbig2_error(ctx, JBIG2_SEVERITY_WARNING, -1, "page %d returned with no associated image", page_number);
                continue;
            }

            ctx->pages[index].state = JBIG2_PAGE_RETURNED;
            jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, -1, "page %d returned to the client", page_number);
            return jbig2_image_reference(ctx, img);
        }
    }

    /* no pages available */
    return NULL;
}