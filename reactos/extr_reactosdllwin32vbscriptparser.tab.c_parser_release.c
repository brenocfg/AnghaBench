#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  heap; } ;
typedef  TYPE_1__ parser_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  heap_pool_free (int /*<<< orphan*/ *) ; 

void parser_release(parser_ctx_t *ctx)
{
    heap_pool_free(&ctx->heap);
}