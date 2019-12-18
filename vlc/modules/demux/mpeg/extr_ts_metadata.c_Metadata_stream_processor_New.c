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
typedef  int /*<<< orphan*/  ts_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pf_reset; int /*<<< orphan*/  pf_push; int /*<<< orphan*/  pf_delete; TYPE_2__* priv; } ;
typedef  TYPE_1__ ts_stream_processor_t ;
typedef  int /*<<< orphan*/  es_out_t ;
struct TYPE_6__ {int /*<<< orphan*/ * p_stream; int /*<<< orphan*/ * out; } ;
typedef  TYPE_2__ Metadata_stream_processor_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  Metadata_stream_processor_Delete ; 
 int /*<<< orphan*/  Metadata_stream_processor_Push ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 void* malloc (int) ; 

ts_stream_processor_t *Metadata_stream_processor_New( ts_stream_t *p_stream, es_out_t *out )
{
    ts_stream_processor_t *h = malloc(sizeof(*h));
    if(!h)
        return NULL;

    Metadata_stream_processor_context_t *ctx = malloc( sizeof(Metadata_stream_processor_context_t) );
    if(!ctx)
    {
        free(h);
        return NULL;
    }
    ctx->out = out;
    ctx->p_stream = p_stream;

    h->priv = ctx;
    h->pf_delete = Metadata_stream_processor_Delete;
    h->pf_push = Metadata_stream_processor_Push;
    h->pf_reset = NULL;

    return h;
}