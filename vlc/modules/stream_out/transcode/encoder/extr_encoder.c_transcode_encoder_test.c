#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int /*<<< orphan*/  transcode_encoder_config_t ;
struct TYPE_8__ {int i_cat; } ;
typedef  TYPE_1__ es_format_t ;

/* Variables and functions */
#define  AUDIO_ES 129 
#define  VIDEO_ES 128 
 int VLC_EGENERIC ; 
 int transcode_encoder_audio_test (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int transcode_encoder_video_test (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ ,TYPE_1__*) ; 

int transcode_encoder_test( vlc_object_t *p_obj,
                            const transcode_encoder_config_t *p_cfg,
                            const es_format_t *p_dec_fmtin,
                            vlc_fourcc_t i_codec_in,
                            es_format_t *p_enc_wanted_in )
{
    switch ( p_dec_fmtin->i_cat )
    {
        case VIDEO_ES:
            return transcode_encoder_video_test( p_obj, p_cfg, p_dec_fmtin,
                                                 i_codec_in, p_enc_wanted_in );
        case AUDIO_ES:
            return transcode_encoder_audio_test( p_obj, p_cfg, p_dec_fmtin,
                                                 i_codec_in, p_enc_wanted_in );
        default:
            return VLC_EGENERIC;
    }
}