#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  p_au; scalar_t__ priv; } ;
typedef  TYPE_1__ ts_stream_processor_t ;
typedef  TYPE_1__ SL_stream_processor_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void SL_stream_processor_Delete( ts_stream_processor_t *h )
{
    SL_stream_processor_context_t *ctx = (SL_stream_processor_context_t *) h->priv;
    block_ChainRelease( ctx->p_au );
    free( ctx );
    free( h );
}