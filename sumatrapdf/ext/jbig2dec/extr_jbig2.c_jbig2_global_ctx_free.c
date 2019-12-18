#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Jbig2GlobalCtx ;
typedef  int /*<<< orphan*/  Jbig2Ctx ;
typedef  int /*<<< orphan*/  Jbig2Allocator ;

/* Variables and functions */
 int /*<<< orphan*/ * jbig2_ctx_free (int /*<<< orphan*/ *) ; 

Jbig2Allocator *
jbig2_global_ctx_free(Jbig2GlobalCtx *global_ctx)
{
    return jbig2_ctx_free((Jbig2Ctx *) global_ctx);
}