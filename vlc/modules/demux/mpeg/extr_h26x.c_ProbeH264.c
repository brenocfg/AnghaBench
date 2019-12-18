#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int b_sps; int b_pps; } ;
typedef  TYPE_1__ h264_probe_ctx_t ;

/* Variables and functions */
 int const H264_NAL_AU_DELIMITER ; 
 int const H264_NAL_PPS ; 
 int const H264_NAL_PREFIX ; 
 int const H264_NAL_SEI ; 
 int const H264_NAL_SLICE_IDR ; 
 int const H264_NAL_SPS ; 
 int const H264_NAL_SPS_EXT ; 
 int const H264_NAL_SUBSET_SPS ; 

__attribute__((used)) static int ProbeH264( const uint8_t *p_peek, size_t i_peek, void *p_priv )
{
    h264_probe_ctx_t *p_ctx = (h264_probe_ctx_t *) p_priv;

    if( i_peek < 1 )
        return -1;
    const uint8_t i_nal_type = p_peek[0] & 0x1F;
    const uint8_t i_ref_idc = p_peek[0] & 0x60;

    if( (p_peek[0] & 0x80) ) /* reserved 0 */
        return -1;

    /* ( !i_ref_idc && (i_nal_type < 6 || i_nal_type == 7 || i_nal_type == 8) ) ||
       (  i_ref_idc && (i_nal_type == 6 || i_nal_type >= 9) ) */

    if( i_nal_type == H264_NAL_SPS )
    {
        if( i_ref_idc == 0 || i_peek < 3 ||
           (p_peek[2] & 0x03) /* reserved 0 bits */ )
            return -1;
        p_ctx->b_sps = true;
    }
    else if( i_nal_type == H264_NAL_PPS )
    {
        if( i_ref_idc == 0 )
            return -1;
        p_ctx->b_pps = true;
    }
    else if( i_nal_type == H264_NAL_SLICE_IDR )
    {
        if( i_ref_idc == 0 || ! p_ctx->b_pps || ! p_ctx->b_sps )
            return -1;
        else
            return 1;
    }
    else if( i_nal_type == H264_NAL_AU_DELIMITER )
    {
        if( i_ref_idc || p_ctx->b_pps || p_ctx->b_sps )
            return -1;
    }
    else if ( i_nal_type == H264_NAL_SEI )
    {
        if( i_ref_idc )
            return -1;
    }
     /* 7.4.1.1 */
    else if ( i_nal_type == H264_NAL_SPS_EXT ||
              i_nal_type == H264_NAL_SUBSET_SPS )
    {
        if( i_ref_idc == 0 || !p_ctx->b_sps )
            return -1;
    }
    else if( i_nal_type == H264_NAL_PREFIX )
    {
        if( i_ref_idc == 0 || !p_ctx->b_pps || !p_ctx->b_sps )
            return -1;
    }
    else return -1; /* see 7.4.1.2.3 for sequence */

    return 0;
}