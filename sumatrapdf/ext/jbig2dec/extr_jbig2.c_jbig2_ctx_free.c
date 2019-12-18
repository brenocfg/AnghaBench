#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int n_segments; int current_page; struct TYPE_7__* pages; int /*<<< orphan*/ * image; struct TYPE_7__* segments; struct TYPE_7__* buf; int /*<<< orphan*/ * allocator; } ;
typedef  TYPE_1__ Jbig2Ctx ;
typedef  int /*<<< orphan*/  Jbig2Allocator ;

/* Variables and functions */
 int /*<<< orphan*/  jbig2_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  jbig2_free_segment (TYPE_1__*,TYPE_1__) ; 
 int /*<<< orphan*/  jbig2_image_release (TYPE_1__*,int /*<<< orphan*/ *) ; 

Jbig2Allocator *
jbig2_ctx_free(Jbig2Ctx *ctx)
{
    Jbig2Allocator *ca;
    int i;

    if (ctx == NULL)
        return NULL;

    ca = ctx->allocator;
    jbig2_free(ca, ctx->buf);
    if (ctx->segments != NULL) {
        for (i = 0; i < ctx->n_segments; i++)
            jbig2_free_segment(ctx, ctx->segments[i]);
        jbig2_free(ca, ctx->segments);
    }

    if (ctx->pages != NULL) {
        for (i = 0; i <= ctx->current_page; i++)
            if (ctx->pages[i].image != NULL)
                jbig2_image_release(ctx, ctx->pages[i].image);
        jbig2_free(ca, ctx->pages);
    }

    jbig2_free(ca, ctx);

    return ca;
}