#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct decoder_owner {TYPE_1__* packetizer; } ;
struct TYPE_21__ {int (* pf_decode ) (TYPE_1__*,TYPE_2__*) ;TYPE_2__* (* pf_get_cc ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  fmt_out; int /*<<< orphan*/  fmt_in; TYPE_2__* (* pf_packetize ) (TYPE_1__*,TYPE_2__**) ;int /*<<< orphan*/ * p_module; } ;
typedef  TYPE_1__ decoder_t ;
typedef  int /*<<< orphan*/  decoder_cc_desc_t ;
struct TYPE_22__ {struct TYPE_22__* p_next; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int VLCDEC_ECRITICAL ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  debug (char*) ; 
 struct decoder_owner* dec_get_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  decoder_Clean (TYPE_1__*) ; 
 scalar_t__ decoder_load (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_IsSimilar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* stub1 (TYPE_1__*,TYPE_2__**) ; 
 int stub2 (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* stub3 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int stub4 (TYPE_1__*,TYPE_2__*) ; 
 int stub5 (TYPE_1__*,TYPE_2__*) ; 

int test_decoder_process(decoder_t *decoder, block_t *p_block)
{
    struct decoder_owner *owner = dec_get_owner(decoder);
    decoder_t *packetizer = owner->packetizer;

    /* This case can happen if a decoder reload failed */
    if (decoder->p_module == NULL)
    {
        if (p_block != NULL)
            block_Release(p_block);
        return VLC_EGENERIC;
    }

    block_t **pp_block = p_block ? &p_block : NULL;
    block_t *p_packetized_block;
    while ((p_packetized_block =
                packetizer->pf_packetize(packetizer, pp_block)))
    {

        if (!es_format_IsSimilar(&decoder->fmt_in, &packetizer->fmt_out))
        {
            debug("restarting module due to input format change\n");

            /* Drain the decoder module */
            decoder->pf_decode(decoder, NULL);

            /* Reload decoder */
            decoder_Clean(decoder);
            if (decoder_load(decoder, false, &packetizer->fmt_out) != VLC_SUCCESS)
            {
                block_ChainRelease(p_packetized_block);
                return VLC_EGENERIC;
            }
        }

        if (packetizer->pf_get_cc)
        {
            decoder_cc_desc_t desc;
            block_t *p_cc = packetizer->pf_get_cc(packetizer, &desc);
            if (p_cc)
                block_Release(p_cc);
        }

        while (p_packetized_block != NULL)
        {

            block_t *p_next = p_packetized_block->p_next;
            p_packetized_block->p_next = NULL;

            int ret = decoder->pf_decode(decoder, p_packetized_block);

            if (ret == VLCDEC_ECRITICAL)
            {
                block_ChainRelease(p_next);
                return VLC_EGENERIC;
            }

            p_packetized_block = p_next;
        }
    }
    if (p_block == NULL) /* Drain */
        decoder->pf_decode(decoder, NULL);
    return VLC_SUCCESS;
}