#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_multiview_mode_t ;
struct TYPE_10__ {int i_frame_rate; int i_frame_rate_base; int /*<<< orphan*/  multiview_mode; } ;
struct TYPE_11__ {scalar_t__ i_codec; TYPE_1__ video; int /*<<< orphan*/  i_original_fourcc; } ;
struct TYPE_12__ {TYPE_2__ fmt; } ;
typedef  TYPE_3__ ts_es_t ;
struct TYPE_13__ {int i_frame_rate_code; int /*<<< orphan*/  b_mpeg2; int /*<<< orphan*/  b_multiple_frame_rate; } ;
typedef  TYPE_4__ dvbpsi_vstream_dr_t ;
typedef  int /*<<< orphan*/  dvbpsi_pmt_es_t ;
struct TYPE_14__ {scalar_t__ i_length; int* p_data; } ;
typedef  TYPE_5__ dvbpsi_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  MULTIVIEW_2D ; 
 int /*<<< orphan*/  MULTIVIEW_STEREO_SBS ; 
 int /*<<< orphan*/  MULTIVIEW_STEREO_TB ; 
 TYPE_5__* PMTEsFindDescriptor (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  VLC_CODEC_MP1V ; 
 scalar_t__ VLC_CODEC_MPGV ; 
 TYPE_4__* dvbpsi_DecodeVStreamDr (TYPE_5__*) ; 

__attribute__((used)) static void PMTSetupEs0x02( ts_es_t *p_es,
                            const dvbpsi_pmt_es_t *p_dvbpsies )
{
    dvbpsi_descriptor_t *p_dr = PMTEsFindDescriptor( p_dvbpsies, 0x02 );
    if( p_dr )
    {
        /* sample: wcbs.ts */
        const dvbpsi_vstream_dr_t *p_vdr = dvbpsi_DecodeVStreamDr( p_dr );
        if( p_vdr )
        {
            if( p_vdr->i_frame_rate_code > 1 && p_vdr->i_frame_rate_code < 9 &&
                !p_vdr->b_multiple_frame_rate )
            {
                static const int code_to_frame_rate[8][2] =
                {
                    { 24000, 1001 }, { 24, 1 }, { 25, 1 },       { 30000, 1001 },
                    { 30, 1 },       { 50, 1 }, { 60000, 1001 }, { 60, 1 },
                };
                p_es->fmt.video.i_frame_rate = code_to_frame_rate[p_vdr->i_frame_rate_code - 1][0];
                p_es->fmt.video.i_frame_rate_base = code_to_frame_rate[p_vdr->i_frame_rate_code - 1][1];
            }
            if( !p_vdr->b_mpeg2 && p_es->fmt.i_codec == VLC_CODEC_MPGV )
                p_es->fmt.i_original_fourcc = VLC_CODEC_MP1V;
        }
    }

    /* MPEG2_stereoscopic_video_format_descriptor */
    p_dr = PMTEsFindDescriptor( p_dvbpsies, 0x34 );
    if( p_dr && p_dr->i_length > 0 && (p_dr->p_data[0] & 0x80) )
    {
        video_multiview_mode_t mode;
        switch( p_dr->p_data[0] & 0x7F )
        {
            case 0x03:
                mode = MULTIVIEW_STEREO_SBS; break;
            case 0x04:
                mode = MULTIVIEW_STEREO_TB; break;
            case 0x08:
            default:
                mode = MULTIVIEW_2D; break;
        }
        p_es->fmt.video.multiview_mode = mode;
    }
}