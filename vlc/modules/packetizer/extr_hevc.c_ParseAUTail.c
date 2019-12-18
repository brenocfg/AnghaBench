#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_15__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_13__ {int /*<<< orphan*/ * p_chain; } ;
struct TYPE_14__ {int /*<<< orphan*/  pp_chain_last; } ;
struct TYPE_16__ {TYPE_1__ frame; int /*<<< orphan*/  b_recovery_point; int /*<<< orphan*/  sets; TYPE_2__ post; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_17__ {int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_END_OF_SEQUENCE ; 
#define  HEVC_NAL_EOB 130 
#define  HEVC_NAL_EOS 129 
#define  HEVC_NAL_SUFF_SEI 128 
 int /*<<< orphan*/  HxxxParse_AnnexB_SEI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  MISSING ; 
 TYPE_5__* OutputQueues (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ParseSEICallback ; 
 int /*<<< orphan*/  block_ChainLastAppend (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static block_t * ParseAUTail(decoder_t *p_dec, uint8_t i_nal_type, block_t *p_nalb)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    block_t *p_ret = NULL;

    block_ChainLastAppend(&p_sys->post.pp_chain_last, p_nalb);

    switch(i_nal_type)
    {
        case HEVC_NAL_EOS:
        case HEVC_NAL_EOB:
            p_ret = OutputQueues(p_sys, p_sys->sets != MISSING &&
                                        p_sys->b_recovery_point);
            if( p_ret )
                p_ret->i_flags |= BLOCK_FLAG_END_OF_SEQUENCE;
            break;

        case HEVC_NAL_SUFF_SEI:
            HxxxParse_AnnexB_SEI( p_nalb->p_buffer, p_nalb->i_buffer,
                                  2 /* nal header */, ParseSEICallback, p_dec );
            break;
    }

    if(!p_ret && p_sys->frame.p_chain == NULL)
        p_ret = OutputQueues(p_sys, false);

    return p_ret;
}