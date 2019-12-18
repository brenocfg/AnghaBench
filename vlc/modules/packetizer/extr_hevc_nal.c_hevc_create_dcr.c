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
typedef  int uint8_t ;
struct hevc_dcr_values {int i_numTemporalLayer; int i_chroma_idc; int i_bit_depth_luma_minus8; int i_bit_depth_chroma_minus8; int b_temporalIdNested; int /*<<< orphan*/  general_configuration; } ;
struct hevc_dcr_params {scalar_t__ i_vps_count; scalar_t__ i_sps_count; scalar_t__ i_pps_count; scalar_t__ i_seipref_count; scalar_t__ i_seisuff_count; int /*<<< orphan*/ * rgi_seisuff; int /*<<< orphan*/ * p_seisuff; int /*<<< orphan*/ * rgi_seipref; int /*<<< orphan*/ * p_seipref; int /*<<< orphan*/ * rgi_pps; int /*<<< orphan*/ * p_pps; int /*<<< orphan*/ * rgi_sps; int /*<<< orphan*/ * p_sps; int /*<<< orphan*/ * rgi_vps; int /*<<< orphan*/ * p_vps; struct hevc_dcr_values* p_values; } ;
struct TYPE_4__ {int chroma_format_idc; int bit_depth_chroma_minus8; int bit_depth_luma_minus8; } ;
typedef  TYPE_1__ hevc_sequence_parameter_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_DCR_ADD_NALS (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEVC_DCR_ADD_SIZES (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEVC_NAL_PPS ; 
 int /*<<< orphan*/  HEVC_NAL_PREF_SEI ; 
 int /*<<< orphan*/  HEVC_NAL_SPS ; 
 int /*<<< orphan*/  HEVC_NAL_SUFF_SEI ; 
 int /*<<< orphan*/  HEVC_NAL_VPS ; 
 int /*<<< orphan*/  SetWBE (int*,int) ; 
 int /*<<< orphan*/  hevc_dcr_params_from_vps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hevc_dcr_values*) ; 
 TYPE_1__* hevc_decode_sps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hevc_rbsp_release_sps (TYPE_1__*) ; 
 int* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

uint8_t * hevc_create_dcr( const struct hevc_dcr_params *p_params,
                           uint8_t i_nal_length_size,
                           bool b_completeness, size_t *pi_size )
{
    *pi_size = 0;

    if( i_nal_length_size != 1 && i_nal_length_size != 2 && i_nal_length_size != 4 )
        return NULL;

    struct hevc_dcr_values values =
    {
        .general_configuration = {0},
        .i_numTemporalLayer = 0,
        .i_chroma_idc = 1,
        .i_bit_depth_luma_minus8 = 0,
        .i_bit_depth_chroma_minus8 = 0,
        .b_temporalIdNested = false,
    };

    if( p_params->p_values != NULL )
    {
        values = *p_params->p_values;
    }
    else
    {
        if( p_params->i_vps_count == 0 || p_params->i_sps_count == 0 )
           return NULL; /* required to extract info */

        hevc_dcr_params_from_vps( p_params->p_vps[0], p_params->rgi_vps[0], &values );

        hevc_sequence_parameter_set_t *p_sps =
                hevc_decode_sps( p_params->p_sps[0], p_params->rgi_sps[0], true );
        if( p_sps )
        {
            values.i_chroma_idc = p_sps->chroma_format_idc;
            values.i_bit_depth_chroma_minus8 = p_sps->bit_depth_chroma_minus8;
            values.i_bit_depth_luma_minus8 = p_sps->bit_depth_luma_minus8;
            hevc_rbsp_release_sps( p_sps );
        }
    }

    size_t i_total_size = 1+12+2+4+2+2;
    HEVC_DCR_ADD_SIZES(p_params->i_vps_count, p_params->rgi_vps);
    HEVC_DCR_ADD_SIZES(p_params->i_sps_count, p_params->rgi_sps);
    HEVC_DCR_ADD_SIZES(p_params->i_pps_count, p_params->rgi_pps);
    HEVC_DCR_ADD_SIZES(p_params->i_seipref_count, p_params->rgi_seipref);
    HEVC_DCR_ADD_SIZES(p_params->i_seisuff_count, p_params->rgi_seisuff);

    uint8_t *p_data = malloc( i_total_size );
    if( p_data == NULL )
        return NULL;

    *pi_size = i_total_size;
    uint8_t *p = p_data;

    /* version */
    *p++ = 0x01;
    memcpy( p, values.general_configuration, 12 ); p += 12;
    /* Don't set min spatial segmentation */
    SetWBE( p, 0xF000 ); p += 2;
    /* Don't set parallelism type since segmentation isn't set */
    *p++ = 0xFC;
    *p++ = (0xFC | (values.i_chroma_idc & 0x03));
    *p++ = (0xF8 | (values.i_bit_depth_luma_minus8 & 0x07));
    *p++ = (0xF8 | (values.i_bit_depth_chroma_minus8 & 0x07));

    /* Don't set framerate */
    SetWBE( p, 0x0000); p += 2;
    /* Force NAL size of 4 bytes that replace the startcode */
    *p++ = ( ((values.i_numTemporalLayer & 0x07) << 3) |
              (values.b_temporalIdNested << 2) |
              (i_nal_length_size - 1) );
    /* total number of arrays */
    *p++ = !!p_params->i_vps_count + !!p_params->i_sps_count +
           !!p_params->i_pps_count + !!p_params->i_seipref_count +
           !!p_params->i_seisuff_count;

    /* Write NAL arrays */
    HEVC_DCR_ADD_NALS(HEVC_NAL_VPS, p_params->i_vps_count,
                      p_params->p_vps, p_params->rgi_vps);
    HEVC_DCR_ADD_NALS(HEVC_NAL_SPS, p_params->i_sps_count,
                      p_params->p_sps, p_params->rgi_sps);
    HEVC_DCR_ADD_NALS(HEVC_NAL_PPS, p_params->i_pps_count,
                      p_params->p_pps, p_params->rgi_pps);
    HEVC_DCR_ADD_NALS(HEVC_NAL_PREF_SEI, p_params->i_seipref_count,
                      p_params->p_seipref, p_params->rgi_seipref);
    HEVC_DCR_ADD_NALS(HEVC_NAL_SUFF_SEI, p_params->i_seisuff_count,
                      p_params->p_seisuff, p_params->rgi_seisuff);

    return p_data;
}