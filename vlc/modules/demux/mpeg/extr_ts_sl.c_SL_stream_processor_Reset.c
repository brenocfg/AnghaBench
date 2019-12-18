#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ priv; } ;
typedef  TYPE_1__ ts_stream_processor_t ;
struct TYPE_5__ {int /*<<< orphan*/ * p_au; int /*<<< orphan*/ ** pp_au_last; } ;
typedef  TYPE_2__ SL_stream_processor_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SL_stream_processor_Reset( ts_stream_processor_t *h )
{
    SL_stream_processor_context_t *ctx = (SL_stream_processor_context_t *) h->priv;
    block_ChainRelease( ctx->p_au );
    ctx->p_au = NULL;
    ctx->pp_au_last = &ctx->p_au;
}