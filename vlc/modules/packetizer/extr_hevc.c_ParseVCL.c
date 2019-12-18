#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  hevc_video_parameter_set_t ;
typedef  int /*<<< orphan*/  hevc_slice_segment_header_t ;
typedef  int /*<<< orphan*/  hevc_sequence_parameter_set_t ;
typedef  int /*<<< orphan*/  hevc_picture_parameter_set_t ;
typedef  enum hevc_slice_type_e { ____Placeholder_hevc_slice_type_e } hevc_slice_type_e ;
struct TYPE_18__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_17__ {int /*<<< orphan*/  pp_chain_last; scalar_t__ p_chain; } ;
struct TYPE_19__ {scalar_t__ sets; int b_recovery_point; TYPE_1__ frame; int /*<<< orphan*/  p_ccs; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_20__ {int* p_buffer; size_t i_buffer; int i_flags; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateSets (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BLOCK_FLAG_TYPE_B ; 
 int BLOCK_FLAG_TYPE_I ; 
 int BLOCK_FLAG_TYPE_P ; 
 scalar_t__ COMPLETE ; 
 int /*<<< orphan*/  GetXPSSet (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
#define  HEVC_NAL_BLA_N_LP 136 
#define  HEVC_NAL_BLA_W_LP 135 
#define  HEVC_NAL_BLA_W_RADL 134 
#define  HEVC_NAL_CRA 133 
#define  HEVC_NAL_IDR_N_LP 132 
#define  HEVC_NAL_IDR_W_RADL 131 
#define  HEVC_SLICE_TYPE_B 130 
#define  HEVC_SLICE_TYPE_I 129 
#define  HEVC_SLICE_TYPE_P 128 
 scalar_t__ MISSING ; 
 TYPE_4__* OutputQueues (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ParseStoredSEI (TYPE_2__*) ; 
 scalar_t__ XPSReady (TYPE_3__*) ; 
 int /*<<< orphan*/  block_ChainLastAppend (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  cc_storage_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hevc_decode_slice_header (int const*,size_t,int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **),TYPE_3__*) ; 
 int hevc_getNALLayer (int const*) ; 
 int /*<<< orphan*/  hevc_get_slice_pps_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hevc_get_slice_type (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  hevc_rbsp_release_slice_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hxxx_strip_AnnexB_startcode (int const**,size_t*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static block_t *ParseVCL(decoder_t *p_dec, uint8_t i_nal_type, block_t *p_frag)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    block_t *p_outputchain = NULL;

    const uint8_t *p_buffer = p_frag->p_buffer;
    size_t i_buffer = p_frag->i_buffer;

    if(unlikely(!hxxx_strip_AnnexB_startcode(&p_buffer, &i_buffer) || i_buffer < 3))
    {
        block_ChainLastAppend(&p_sys->frame.pp_chain_last, p_frag); /* might be corrupted */
        return NULL;
    }

    const uint8_t i_layer = hevc_getNALLayer( p_buffer );
    bool b_first_slice_in_pic = p_buffer[2] & 0x80;
    if (b_first_slice_in_pic)
    {
        if(p_sys->frame.p_chain)
        {
            /* Starting new frame: return previous frame data for output */
            p_outputchain = OutputQueues(p_sys, p_sys->sets != MISSING &&
                                                p_sys->b_recovery_point);
        }

        hevc_slice_segment_header_t *p_sli = hevc_decode_slice_header(p_buffer, i_buffer, true,
                                                                      GetXPSSet, p_sys);
        if(p_sli && i_layer == 0)
        {
            hevc_sequence_parameter_set_t *p_sps;
            hevc_picture_parameter_set_t *p_pps;
            hevc_video_parameter_set_t *p_vps;
            GetXPSSet(hevc_get_slice_pps_id(p_sli), p_sys, &p_pps, &p_sps, &p_vps);
            ActivateSets(p_dec, p_pps, p_sps, p_vps);
        }

        ParseStoredSEI( p_dec );

        switch(i_nal_type)
        {
            case HEVC_NAL_BLA_W_LP:
            case HEVC_NAL_BLA_W_RADL:
            case HEVC_NAL_BLA_N_LP:
            case HEVC_NAL_IDR_W_RADL:
            case HEVC_NAL_IDR_N_LP:
            case HEVC_NAL_CRA:
                p_frag->i_flags |= BLOCK_FLAG_TYPE_I;
                break;

            default:
            {
                if(p_sli)
                {
                    enum hevc_slice_type_e type;
                    if(hevc_get_slice_type( p_sli, &type ))
                    {
                        switch(type)
                        {
                            case HEVC_SLICE_TYPE_B:
                                p_frag->i_flags |= BLOCK_FLAG_TYPE_B;
                                break;
                            case HEVC_SLICE_TYPE_P:
                                p_frag->i_flags |= BLOCK_FLAG_TYPE_P;
                                break;
                            case HEVC_SLICE_TYPE_I:
                                p_frag->i_flags |= BLOCK_FLAG_TYPE_I;
                                break;
                        }
                    }
                }
                else p_frag->i_flags |= BLOCK_FLAG_TYPE_B;
            }
            break;
        }

        if(p_sli)
            hevc_rbsp_release_slice_header(p_sli);
    }

    if(p_sys->sets == MISSING && i_layer == 0 && XPSReady(p_sys))
        p_sys->sets = COMPLETE;

    if(p_sys->sets != MISSING && (p_frag->i_flags & BLOCK_FLAG_TYPE_I))
    {
        p_sys->b_recovery_point = true; /* won't care about SEI recovery */
    }

    if(!p_sys->b_recovery_point) /* content will be dropped */
        cc_storage_reset(p_sys->p_ccs);

    block_ChainLastAppend(&p_sys->frame.pp_chain_last, p_frag);

    return p_outputchain;
}