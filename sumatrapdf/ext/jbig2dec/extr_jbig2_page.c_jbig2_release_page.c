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
struct TYPE_7__ {int max_page_index; TYPE_1__* pages; } ;
struct TYPE_6__ {int /*<<< orphan*/  number; int /*<<< orphan*/  state; int /*<<< orphan*/ * image; } ;
typedef  int /*<<< orphan*/  Jbig2Image ;
typedef  TYPE_2__ Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_PAGE_RELEASED ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_DEBUG ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int /*<<< orphan*/  jbig2_error (TYPE_2__*,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  jbig2_image_release (TYPE_2__*,int /*<<< orphan*/ *) ; 

void
jbig2_release_page(Jbig2Ctx *ctx, Jbig2Image *image)
{
    int index;

    if (image == NULL)
        return;

    /* find the matching page struct and mark it released */
    for (index = 0; index < ctx->max_page_index; index++) {
        if (ctx->pages[index].image == image) {
            jbig2_image_release(ctx, image);
            ctx->pages[index].state = JBIG2_PAGE_RELEASED;
            jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, -1, "page %d released by the client", ctx->pages[index].number);
            return;
        }
    }

    /* no matching pages */
    jbig2_error(ctx, JBIG2_SEVERITY_WARNING, -1, "failed to release unknown page");
}