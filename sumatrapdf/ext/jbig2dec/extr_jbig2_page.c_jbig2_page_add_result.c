#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {int height; int flags; TYPE_2__* image; scalar_t__ striped; } ;
typedef  TYPE_1__ Jbig2Page ;
typedef  TYPE_2__ Jbig2Image ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;
typedef  int /*<<< orphan*/  Jbig2ComposeOp ;

/* Variables and functions */
 int /*<<< orphan*/  JBIG2_SEVERITY_DEBUG ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_FATAL ; 
 int /*<<< orphan*/  JBIG2_SEVERITY_WARNING ; 
 int jbig2_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,...) ; 
 int jbig2_image_compose (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* jbig2_image_resize (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int) ; 

int
jbig2_page_add_result(Jbig2Ctx *ctx, Jbig2Page *page, Jbig2Image *image, uint32_t x, uint32_t y, Jbig2ComposeOp op)
{
    int code;

    /* ensure image exists first */
    if (page->image == NULL)
        return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, -1, "page info possibly missing, no image defined");

    /* grow the page to accommodate a new stripe if necessary */
    if (page->striped && page->height == 0xFFFFFFFF) {
        uint32_t new_height = y + image->height;
        if (page->image->height < new_height) {
            Jbig2Image *resized_image = NULL;

            jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, -1, "growing page buffer to %u rows to accommodate new stripe", new_height);
            resized_image = jbig2_image_resize(ctx, page->image, page->image->width, new_height, page->flags & 4);
            if (resized_image == NULL) {
                return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "unable to resize image to accommodate new stripe");
            }
            page->image = resized_image;
        }
    }

    code = jbig2_image_compose(ctx, page->image, image, x, y, op);
    if (code < 0)
        return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, -1, "failed to compose image with page");

    return 0;
}