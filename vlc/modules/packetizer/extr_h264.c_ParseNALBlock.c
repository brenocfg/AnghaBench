#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_29__ {int i_idr_pic_id; } ;
typedef  TYPE_3__ h264_slice_t ;
struct TYPE_30__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_28__ {int /*<<< orphan*/  pp_append; } ;
struct TYPE_27__ {int /*<<< orphan*/  pp_append; TYPE_6__* p_head; } ;
struct TYPE_31__ {int b_slice; int b_recovered; int b_new_sps; int b_new_pps; scalar_t__ i_frame_dts; scalar_t__ i_frame_pts; int /*<<< orphan*/  dts; TYPE_2__ frame; int /*<<< orphan*/  i_next_block_flags; TYPE_1__ leading; int /*<<< orphan*/ * p_active_pps; TYPE_3__ slice; void* i_recoveryfnum; void* i_recovery_frame_cnt; int /*<<< orphan*/  p_ccs; int /*<<< orphan*/  p_active_sps; } ;
typedef  TYPE_5__ decoder_sys_t ;
struct TYPE_32__ {int* p_buffer; scalar_t__ i_dts; scalar_t__ i_pts; int i_flags; int /*<<< orphan*/  i_buffer; struct TYPE_32__* p_next; } ;
typedef  TYPE_6__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_AU_END ; 
 int BLOCK_FLAG_DROP ; 
 int /*<<< orphan*/  BLOCK_FLAG_END_OF_SEQUENCE ; 
 int BLOCK_FLAG_PRIVATE_AUD ; 
 int BLOCK_FLAG_PRIVATE_SEI ; 
 int /*<<< orphan*/  DropStoredNAL (TYPE_5__*) ; 
#define  H264_NAL_AU_DELIMITER 151 
#define  H264_NAL_DEPTH_PS 150 
#define  H264_NAL_END_OF_SEQ 149 
#define  H264_NAL_END_OF_STREAM 148 
#define  H264_NAL_FILLER_DATA 147 
#define  H264_NAL_PPS 146 
#define  H264_NAL_PREFIX 145 
#define  H264_NAL_RESERVED_17 144 
#define  H264_NAL_RESERVED_18 143 
#define  H264_NAL_RESERVED_22 142 
#define  H264_NAL_RESERVED_23 141 
#define  H264_NAL_SEI 140 
#define  H264_NAL_SLICE 139 
#define  H264_NAL_SLICE_3D_EXT 138 
#define  H264_NAL_SLICE_DPA 137 
#define  H264_NAL_SLICE_DPB 136 
#define  H264_NAL_SLICE_DPC 135 
#define  H264_NAL_SLICE_EXT 134 
#define  H264_NAL_SLICE_IDR 133 
#define  H264_NAL_SLICE_WP 132 
#define  H264_NAL_SPS 131 
#define  H264_NAL_SPS_EXT 130 
#define  H264_NAL_SUBSET_SPS 129 
#define  H264_NAL_UNKNOWN 128 
 int /*<<< orphan*/  HxxxParse_AnnexB_SEI (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int IsFirstVCLNALUnit (TYPE_3__*,TYPE_3__*) ; 
 TYPE_6__* OutputPicture (TYPE_4__*) ; 
 int /*<<< orphan*/  ParseSeiCallback ; 
 int /*<<< orphan*/  ParseSliceHeader (TYPE_4__*,TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  PutPPS (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  PutSPS (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ResetOutputVariables (TYPE_5__*) ; 
 void* UINT_MAX ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_ChainLastAppend (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_6__*) ; 
 int /*<<< orphan*/  cc_storage_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__ const) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_4__*,char*) ; 

__attribute__((used)) static block_t *ParseNALBlock( decoder_t *p_dec, bool *pb_ts_used, block_t *p_frag )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    block_t *p_pic = NULL;

    const int i_nal_type = p_frag->p_buffer[4]&0x1f;
    const vlc_tick_t i_frag_dts = p_frag->i_dts;
    const vlc_tick_t i_frag_pts = p_frag->i_pts;
    bool b_au_end = p_frag->i_flags & BLOCK_FLAG_AU_END;
    p_frag->i_flags &= ~BLOCK_FLAG_AU_END;

    if( p_sys->b_slice && (!p_sys->p_active_pps || !p_sys->p_active_sps) )
    {
        msg_Warn( p_dec, "waiting for SPS/PPS" );

        /* Reset context */
        DropStoredNAL( p_sys );
        ResetOutputVariables( p_sys );
        cc_storage_reset( p_sys->p_ccs );
    }

    switch( i_nal_type )
    {
        /*** Slices ***/
        case H264_NAL_SLICE:
        case H264_NAL_SLICE_DPA:
        case H264_NAL_SLICE_DPB:
        case H264_NAL_SLICE_DPC:
        case H264_NAL_SLICE_IDR:
        {
            h264_slice_t newslice;

            if( i_nal_type == H264_NAL_SLICE_IDR )
            {
                p_sys->b_recovered = true;
                p_sys->i_recovery_frame_cnt = UINT_MAX;
                p_sys->i_recoveryfnum = UINT_MAX;
            }

            if( ParseSliceHeader( p_dec, p_frag, &newslice ) )
            {
                /* Only IDR carries the id, to be propagated */
                if( newslice.i_idr_pic_id == -1 )
                    newslice.i_idr_pic_id = p_sys->slice.i_idr_pic_id;

                bool b_new_picture = IsFirstVCLNALUnit( &p_sys->slice, &newslice );
                if( b_new_picture )
                {
                    /* Parse SEI for that frame now we should have matched SPS/PPS */
                    for( block_t *p_sei = p_sys->leading.p_head; p_sei; p_sei = p_sei->p_next )
                    {
                        if( (p_sei->i_flags & BLOCK_FLAG_PRIVATE_SEI) == 0 )
                            continue;
                        HxxxParse_AnnexB_SEI( p_sei->p_buffer, p_sei->i_buffer,
                                              1 /* nal header */, ParseSeiCallback, p_dec );
                    }

                    if( p_sys->b_slice )
                        p_pic = OutputPicture( p_dec );
                }

                /* */
                p_sys->slice = newslice;
            }
            else
            {
                p_sys->p_active_pps = NULL;
                /* Fragment will be discarded later on */
            }
            p_sys->b_slice = true;

            block_ChainLastAppend( &p_sys->frame.pp_append, p_frag );
        } break;

        /*** Prefix NALs ***/

        case H264_NAL_AU_DELIMITER:
            if( p_sys->b_slice )
                p_pic = OutputPicture( p_dec );

            /* clear junk if no pic, we're always the first nal */
            DropStoredNAL( p_sys );

            p_frag->i_flags |= BLOCK_FLAG_PRIVATE_AUD;

            block_ChainLastAppend( &p_sys->leading.pp_append, p_frag );
        break;

        case H264_NAL_SPS:
        case H264_NAL_PPS:
            if( p_sys->b_slice )
                p_pic = OutputPicture( p_dec );

            /* Stored for insert on keyframes */
            if( i_nal_type == H264_NAL_SPS )
            {
                PutSPS( p_dec, p_frag );
                p_sys->b_new_sps = true;
            }
            else
            {
                PutPPS( p_dec, p_frag );
                p_sys->b_new_pps = true;
            }
        break;

        case H264_NAL_SEI:
            if( p_sys->b_slice )
                p_pic = OutputPicture( p_dec );

            p_frag->i_flags |= BLOCK_FLAG_PRIVATE_SEI;
            block_ChainLastAppend( &p_sys->leading.pp_append, p_frag );
        break;

        case H264_NAL_SPS_EXT:
        case H264_NAL_PREFIX: /* first slice/VCL associated data */
        case H264_NAL_SUBSET_SPS:
        case H264_NAL_DEPTH_PS:
        case H264_NAL_RESERVED_17:
        case H264_NAL_RESERVED_18:
            if( p_sys->b_slice )
                p_pic = OutputPicture( p_dec );

            block_ChainLastAppend( &p_sys->leading.pp_append, p_frag );
        break;

        /*** Suffix NALs ***/

        case H264_NAL_END_OF_SEQ:
        case H264_NAL_END_OF_STREAM:
            /* Early end of packetization */
            block_ChainLastAppend( &p_sys->frame.pp_append, p_frag );

            /* important for still pictures/menus */
            p_sys->i_next_block_flags |= BLOCK_FLAG_END_OF_SEQUENCE;
            if( p_sys->b_slice )
                p_pic = OutputPicture( p_dec );
        break;

        case H264_NAL_SLICE_WP: // post
        case H264_NAL_UNKNOWN:
        case H264_NAL_FILLER_DATA:
        case H264_NAL_SLICE_EXT:
        case H264_NAL_SLICE_3D_EXT:
        case H264_NAL_RESERVED_22:
        case H264_NAL_RESERVED_23:
        default: /* others 24..31, including unknown */
            block_ChainLastAppend( &p_sys->frame.pp_append, p_frag );
        break;
    }

    *pb_ts_used = false;
    if( p_sys->i_frame_dts == VLC_TICK_INVALID &&
        p_sys->i_frame_pts == VLC_TICK_INVALID )
    {
        p_sys->i_frame_dts = i_frag_dts;
        p_sys->i_frame_pts = i_frag_pts;
        *pb_ts_used = true;
        if( i_frag_dts != VLC_TICK_INVALID )
            date_Set( &p_sys->dts, i_frag_dts );
    }

    if( p_sys->b_slice && b_au_end && !p_pic )
    {
        p_pic = OutputPicture( p_dec );
    }

    if( p_pic && (p_pic->i_flags & BLOCK_FLAG_DROP) )
    {
        block_Release( p_pic );
        p_pic = NULL;
    }

    return p_pic;
}