#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  allocator; } ;
struct TYPE_8__ {size_t n_symbols; struct TYPE_8__* glyphs; } ;
typedef  TYPE_1__ Jbig2SymbolDict ;
typedef  TYPE_2__ Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  jbig2_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  jbig2_image_release (TYPE_2__*,TYPE_1__) ; 

void
jbig2_sd_release(Jbig2Ctx *ctx, Jbig2SymbolDict *dict)
{
    uint32_t i;

    if (dict == NULL)
        return;
    if (dict->glyphs != NULL)
        for (i = 0; i < dict->n_symbols; i++)
            jbig2_image_release(ctx, dict->glyphs[i]);
    jbig2_free(ctx->allocator, dict->glyphs);
    jbig2_free(ctx->allocator, dict);
}