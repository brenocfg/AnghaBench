#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * palette; int /*<<< orphan*/  i_original_frame_height; int /*<<< orphan*/  i_original_frame_width; } ;
struct TYPE_9__ {TYPE_1__ spu; } ;
struct TYPE_10__ {scalar_t__ i_codec; int i_extra; TYPE_2__ subs; scalar_t__ p_extra; int /*<<< orphan*/  i_bitrate; scalar_t__ i_original_fourcc; int /*<<< orphan*/  i_profile; int /*<<< orphan*/  i_cat; } ;
struct TYPE_11__ {TYPE_3__ fmt; int /*<<< orphan*/  i_track_ID; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
typedef  TYPE_4__ mp4_track_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_12__ {int i_objectProfileIndication; int i_decoder_specific_info_len; int /*<<< orphan*/  p_decoder_specific_info; int /*<<< orphan*/  i_avg_bitrate; } ;
typedef  TYPE_5__ MP4_descriptor_decoder_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  GetDWBE (char*) ; 
 int /*<<< orphan*/  MPEG4_Codec_By_ObjectType (int,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  SPU_PALETTE_DEFINED ; 
 scalar_t__ VLC_CODEC_QCELP ; 
 scalar_t__ VLC_CODEC_SPU ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SetupESDS( demux_t *p_demux, mp4_track_t *p_track, const MP4_descriptor_decoder_config_t *p_decconfig )
{
    /* First update information based on i_objectTypeIndication */
    switch( p_decconfig->i_objectProfileIndication )
    {
        /* Private ID */
    case( 0xe0 ): /* NeroDigital: dvd subs */
        if( p_track->fmt.i_cat == SPU_ES )
        {
            p_track->fmt.i_codec = VLC_CODEC_SPU;
            if( p_track->i_width > 0 )
                p_track->fmt.subs.spu.i_original_frame_width = p_track->i_width;
            if( p_track->i_height > 0 )
                p_track->fmt.subs.spu.i_original_frame_height = p_track->i_height;
        }
        break;
    case( 0xe1 ): /* QCelp for 3gp */
        if( p_track->fmt.i_cat == AUDIO_ES )
        {
            p_track->fmt.i_codec = VLC_CODEC_QCELP;
        }
        break;

        /* Fallback */
    default:
        if( MPEG4_Codec_By_ObjectType( p_decconfig->i_objectProfileIndication,
                                       p_decconfig->p_decoder_specific_info,
                                       p_decconfig->i_decoder_specific_info_len,
                                       &p_track->fmt.i_codec,
                                       &p_track->fmt.i_profile ) )
            break;
        /* Unknown entry, but don't touch i_fourcc */
        msg_Warn( p_demux,
                  "unknown objectProfileIndication(0x%x) (Track[ID 0x%x])",
                  p_decconfig->i_objectProfileIndication,
                  p_track->i_track_ID );
        return;
    }

    p_track->fmt.i_original_fourcc = 0; /* so we don't have MP4A as original fourcc */
    p_track->fmt.i_bitrate = p_decconfig->i_avg_bitrate;

    p_track->fmt.i_extra = p_decconfig->i_decoder_specific_info_len;
    if( p_track->fmt.i_extra > 0 )
    {
        p_track->fmt.p_extra = malloc( p_track->fmt.i_extra );
        memcpy( p_track->fmt.p_extra, p_decconfig->p_decoder_specific_info,
                p_track->fmt.i_extra );
    }
    if( p_track->fmt.i_codec == VLC_CODEC_SPU &&
            p_track->fmt.i_extra >= 16 * 4 )
    {
        for( int i = 0; i < 16; i++ )
        {
            p_track->fmt.subs.spu.palette[1 + i] =
                    GetDWBE((char*)p_track->fmt.p_extra + i * 4);
        }
        p_track->fmt.subs.spu.palette[0] = SPU_PALETTE_DEFINED;
    }
}