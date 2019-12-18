#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_19__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_18__ {int /*<<< orphan*/  pp_chain_last; int /*<<< orphan*/  p_chain; } ;
struct TYPE_17__ {scalar_t__ p_chain; } ;
struct TYPE_16__ {scalar_t__ p_chain; } ;
struct TYPE_20__ {scalar_t__ sets; TYPE_3__ pre; scalar_t__ b_recovery_point; TYPE_2__ frame; TYPE_1__ post; } ;
typedef  TYPE_5__ decoder_sys_t ;
struct TYPE_21__ {int* p_buffer; size_t i_buffer; } ;
typedef  TYPE_6__ block_t ;

/* Variables and functions */
#define  HEVC_NAL_AUD 132 
#define  HEVC_NAL_PPS 131 
#define  HEVC_NAL_PREF_SEI 130 
#define  HEVC_NAL_SPS 129 
#define  HEVC_NAL_VPS 128 
 int /*<<< orphan*/  InsertXPS (TYPE_4__*,int,int,TYPE_6__*) ; 
 scalar_t__ MISSING ; 
 TYPE_6__* OutputQueues (TYPE_5__*,int) ; 
 scalar_t__ SENT ; 
 int /*<<< orphan*/  block_ChainLastAppend (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_6__*) ; 
 int /*<<< orphan*/  hevc_get_xps_id (int*,size_t,int*) ; 
 int /*<<< orphan*/  hxxx_strip_AnnexB_startcode (int const**,size_t*) ; 

__attribute__((used)) static block_t * ParseAUHead(decoder_t *p_dec, uint8_t i_nal_type, block_t *p_nalb)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    block_t *p_ret = NULL;

    if(p_sys->post.p_chain || p_sys->frame.p_chain)
        p_ret = OutputQueues(p_sys, p_sys->sets != MISSING &&
                                    p_sys->b_recovery_point);

    switch(i_nal_type)
    {
        case HEVC_NAL_AUD:
            if(!p_ret && p_sys->pre.p_chain)
                p_ret = OutputQueues(p_sys, p_sys->sets != MISSING &&
                                            p_sys->b_recovery_point);
            break;

        case HEVC_NAL_VPS:
        case HEVC_NAL_SPS:
        case HEVC_NAL_PPS:
        {
            uint8_t i_id;
            const uint8_t *p_xps = p_nalb->p_buffer;
            size_t i_xps = p_nalb->i_buffer;
            if(hxxx_strip_AnnexB_startcode(&p_xps, &i_xps) &&
               hevc_get_xps_id(p_nalb->p_buffer, p_nalb->i_buffer, &i_id))
                InsertXPS(p_dec, i_nal_type, i_id, p_nalb);
            if(p_sys->sets != SENT) /* will store/inject on first recovery point */
            {
                block_Release(p_nalb);
                return p_ret;
            }
            break;
        }

        case HEVC_NAL_PREF_SEI:
            /* stored an parsed later when we get sps & frame */
        default:
            break;
    }

    block_ChainLastAppend(&p_sys->pre.pp_chain_last, p_nalb);

    return p_ret;
}