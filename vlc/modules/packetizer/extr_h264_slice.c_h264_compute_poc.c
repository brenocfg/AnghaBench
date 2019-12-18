#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int int64_t ;
typedef  unsigned int int32_t ;
struct TYPE_9__ {scalar_t__ i_nal_type; int i_pic_order_cnt_lsb; scalar_t__ i_nal_ref_idc; unsigned int i_frame_num; unsigned int i_delta_pic_order_cnt0; int i_delta_pic_order_cnt1; scalar_t__ i_bottom_field_flag; scalar_t__ i_field_pic_flag; scalar_t__ has_mmco5; scalar_t__ i_delta_pic_order_cnt_bottom; } ;
typedef  TYPE_2__ h264_slice_t ;
struct TYPE_10__ {int i_pic_order_cnt_type; int i_log2_max_pic_order_cnt_lsb; int i_log2_max_frame_num; int i_num_ref_frames_in_pic_order_cnt_cycle; unsigned int* offset_for_ref_frame; unsigned int offset_for_non_ref_pic; int offset_for_top_to_bottom_field; } ;
typedef  TYPE_3__ h264_sequence_parameter_set_t ;
struct TYPE_8__ {int lsb; int msb; } ;
struct TYPE_11__ {int prevRefPictureIsBottomField; int prevRefPictureTFOC; unsigned int prevFrameNum; unsigned int prevFrameNumOffset; TYPE_1__ prevPicOrderCnt; scalar_t__ prevRefPictureHasMMCO5; } ;
typedef  TYPE_4__ h264_poc_context_t ;

/* Variables and functions */
 scalar_t__ H264_NAL_SLICE_IDR ; 
 int __MIN (int,int) ; 

void h264_compute_poc( const h264_sequence_parameter_set_t *p_sps,
                       const h264_slice_t *p_slice, h264_poc_context_t *p_ctx,
                       int *p_PictureOrderCount, int *p_tFOC, int *p_bFOC )
{
    *p_tFOC = *p_bFOC = 0;

    if( p_sps->i_pic_order_cnt_type == 0 )
    {
        unsigned maxPocLSB = 1U << (p_sps->i_log2_max_pic_order_cnt_lsb  + 4);

        /* POC reference */
        if( p_slice->i_nal_type == H264_NAL_SLICE_IDR )
        {
            p_ctx->prevPicOrderCnt.lsb = 0;
            p_ctx->prevPicOrderCnt.msb = 0;
        }
        else if( p_ctx->prevRefPictureHasMMCO5 )
        {
            p_ctx->prevPicOrderCnt.msb = 0;
            if( !p_ctx->prevRefPictureIsBottomField )
                p_ctx->prevPicOrderCnt.lsb = p_ctx->prevRefPictureTFOC;
            else
                p_ctx->prevPicOrderCnt.lsb = 0;
        }

        /* 8.2.1.1 */
        int pocMSB = p_ctx->prevPicOrderCnt.msb;
        int64_t orderDiff = p_slice->i_pic_order_cnt_lsb - p_ctx->prevPicOrderCnt.lsb;
        if( orderDiff < 0 && -orderDiff >= maxPocLSB / 2 )
            pocMSB += maxPocLSB;
        else if( orderDiff > maxPocLSB / 2 )
            pocMSB -= maxPocLSB;

        *p_tFOC = *p_bFOC = pocMSB + p_slice->i_pic_order_cnt_lsb;
        if( p_slice->i_field_pic_flag )
            *p_bFOC += p_slice->i_delta_pic_order_cnt_bottom;

        /* Save from ref picture */
        if( p_slice->i_nal_ref_idc /* Is reference */ )
        {
            p_ctx->prevRefPictureIsBottomField = (p_slice->i_field_pic_flag &&
                                                  p_slice->i_bottom_field_flag);
            p_ctx->prevRefPictureHasMMCO5 = p_slice->has_mmco5;
            p_ctx->prevRefPictureTFOC = *p_tFOC;
            p_ctx->prevPicOrderCnt.lsb = p_slice->i_pic_order_cnt_lsb;
            p_ctx->prevPicOrderCnt.msb = pocMSB;
        }
    }
    else
    {
        unsigned maxFrameNum = 1 << (p_sps->i_log2_max_frame_num + 4);
        unsigned frameNumOffset;
        unsigned expectedPicOrderCnt = 0;

        if( p_slice->i_nal_type == H264_NAL_SLICE_IDR )
            frameNumOffset = 0;
        else if( p_ctx->prevFrameNum > p_slice->i_frame_num )
            frameNumOffset = p_ctx->prevFrameNumOffset + maxFrameNum;
        else
            frameNumOffset = p_ctx->prevFrameNumOffset;

        if( p_sps->i_pic_order_cnt_type == 1 )
        {
            unsigned absFrameNum;

            if( p_sps->i_num_ref_frames_in_pic_order_cnt_cycle > 0 )
                absFrameNum = frameNumOffset + p_slice->i_frame_num;
            else
                absFrameNum = 0;

            if( p_slice->i_nal_ref_idc == 0 && absFrameNum > 0 )
                absFrameNum--;

            if( absFrameNum > 0 )
            {
                int32_t expectedDeltaPerPicOrderCntCycle = 0;
                for( int i=0; i<p_sps->i_num_ref_frames_in_pic_order_cnt_cycle; i++ )
                    expectedDeltaPerPicOrderCntCycle += p_sps->offset_for_ref_frame[i];

                unsigned picOrderCntCycleCnt = 0;
                unsigned frameNumInPicOrderCntCycle = 0;
                if( p_sps->i_num_ref_frames_in_pic_order_cnt_cycle )
                {
                    picOrderCntCycleCnt = ( absFrameNum - 1 ) / p_sps->i_num_ref_frames_in_pic_order_cnt_cycle;
                    frameNumInPicOrderCntCycle = ( absFrameNum - 1 ) % p_sps->i_num_ref_frames_in_pic_order_cnt_cycle;
                }

                expectedPicOrderCnt = picOrderCntCycleCnt * expectedDeltaPerPicOrderCntCycle;
                for( unsigned i=0; i <= frameNumInPicOrderCntCycle; i++ )
                    expectedPicOrderCnt = expectedPicOrderCnt + p_sps->offset_for_ref_frame[i];
            }

            if( p_slice->i_nal_ref_idc == 0 )
                expectedPicOrderCnt = expectedPicOrderCnt + p_sps->offset_for_non_ref_pic;

            *p_tFOC = expectedPicOrderCnt + p_slice->i_delta_pic_order_cnt0;
            if( !p_slice->i_field_pic_flag )
                *p_bFOC = *p_tFOC + p_sps->offset_for_top_to_bottom_field + p_slice->i_delta_pic_order_cnt1;
            else if( p_slice->i_bottom_field_flag )
                *p_bFOC = expectedPicOrderCnt + p_sps->offset_for_top_to_bottom_field + p_slice->i_delta_pic_order_cnt0;
        }
        else if( p_sps->i_pic_order_cnt_type == 2 )
        {
            unsigned tempPicOrderCnt;

            if( p_slice->i_nal_type == H264_NAL_SLICE_IDR )
                tempPicOrderCnt = 0;
            else if( p_slice->i_nal_ref_idc == 0 )
                tempPicOrderCnt = 2 * ( frameNumOffset + p_slice->i_frame_num ) - 1;
            else
                tempPicOrderCnt = 2 * ( frameNumOffset + p_slice->i_frame_num );

            *p_bFOC = *p_tFOC = tempPicOrderCnt;
        }

        p_ctx->prevFrameNum = p_slice->i_frame_num;
        if( p_slice->has_mmco5 )
            p_ctx->prevFrameNumOffset = 0;
        else
            p_ctx->prevFrameNumOffset = frameNumOffset;
    }

    /* 8.2.1 (8-1) */
    if( !p_slice->i_field_pic_flag ) /* progressive or contains both fields */
        *p_PictureOrderCount = __MIN( *p_bFOC, *p_tFOC );
    else /* split top or bottom field */
    if ( p_slice->i_bottom_field_flag )
        *p_PictureOrderCount = *p_bFOC;
    else
        *p_PictureOrderCount = *p_tFOC;
}