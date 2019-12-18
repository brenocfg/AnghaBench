#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct test_es_out_t {int dummy; } ;
typedef  int /*<<< orphan*/  es_out_t ;
struct TYPE_4__ {scalar_t__ decoder; } ;
typedef  TYPE_1__ es_out_id_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  EsOutCheckId (struct test_es_out_t*,TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_decoder_process (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int EsOutSend(es_out_t *out, es_out_id_t *id, block_t *block)
{
    struct test_es_out_t *ctx = (struct test_es_out_t *) out;

    //debug("[%p] Sent    ES: %zu\n", (void *)idd, block->i_buffer);
    EsOutCheckId(ctx, id);
#ifdef HAVE_DECODERS
    if (id->decoder)
        test_decoder_process(id->decoder, block);
    else
#endif
        block_Release(block);
    return VLC_SUCCESS;
}