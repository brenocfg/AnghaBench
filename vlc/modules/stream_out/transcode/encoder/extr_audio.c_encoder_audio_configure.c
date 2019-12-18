#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t i_channels; scalar_t__ i_sample_rate; int /*<<< orphan*/  i_bitrate; } ;
struct TYPE_14__ {TYPE_2__ audio; int /*<<< orphan*/  i_codec; scalar_t__ psz_lang; int /*<<< orphan*/  p_config_chain; } ;
typedef  TYPE_4__ transcode_encoder_config_t ;
struct TYPE_16__ {size_t i_channels; void* i_physical_channels; int /*<<< orphan*/  i_format; scalar_t__ i_rate; int /*<<< orphan*/  i_bitspersample; } ;
struct TYPE_13__ {int /*<<< orphan*/  i_codec; void* psz_language; TYPE_6__ audio; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_bitrate; TYPE_6__ audio; int /*<<< orphan*/  i_codec; void* psz_language; } ;
struct TYPE_15__ {TYPE_3__ fmt_in; TYPE_1__ fmt_out; int /*<<< orphan*/  p_cfg; } ;
typedef  TYPE_5__ encoder_t ;
typedef  TYPE_6__ audio_format_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_6__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 void** pi_channels_maps ; 
 void* strdup (scalar_t__) ; 

__attribute__((used)) static int encoder_audio_configure( const transcode_encoder_config_t *p_cfg,
                                    const audio_format_t *p_dec_out,
                                    encoder_t *p_enc, bool b_keep_fmtin )
{
    audio_format_t *p_enc_in = &p_enc->fmt_in.audio;
    audio_format_t *p_enc_out = &p_enc->fmt_out.audio;

    p_enc->p_cfg = p_cfg->p_config_chain;

    if ( p_cfg->psz_lang )
    {
        free( p_enc->fmt_in.psz_language );
        free( p_enc->fmt_out.psz_language );
        p_enc->fmt_in.psz_language = strdup( p_cfg->psz_lang );
        p_enc->fmt_out.psz_language = strdup( p_cfg->psz_lang );
    }

    /* Complete destination format */
    p_enc->fmt_out.i_codec = p_cfg->i_codec;
    p_enc->fmt_out.audio.i_format = p_cfg->i_codec;
    p_enc->fmt_out.i_bitrate = p_cfg->audio.i_bitrate;
    p_enc_out->i_rate = p_cfg->audio.i_sample_rate ? p_cfg->audio.i_sample_rate
                                                   : p_dec_out->i_rate;
    p_enc_out->i_bitspersample = p_dec_out->i_bitspersample;
    p_enc_out->i_channels = p_cfg->audio.i_channels ? p_cfg->audio.i_channels
                                                    : p_dec_out->i_channels;
    aout_FormatPrepare( p_enc_out );
    assert(p_enc_out->i_channels > 0);
    if( p_enc_out->i_channels >= ARRAY_SIZE(pi_channels_maps) )
        p_enc_out->i_channels = ARRAY_SIZE(pi_channels_maps) - 1;

    p_enc_out->i_physical_channels = pi_channels_maps[p_enc_out->i_channels];

    if( b_keep_fmtin ) /* This is tested/wanted decoder fmtin */
        return VLC_SUCCESS;

    p_enc_in->i_physical_channels = p_enc_out->i_physical_channels;

    /* Initialization of encoder format structures */
    p_enc->fmt_in.i_codec = p_dec_out->i_format;
    p_enc_in->i_format = p_dec_out->i_format;
    p_enc_in->i_rate = p_enc_out->i_rate;
    p_enc_in->i_physical_channels = p_enc_out->i_physical_channels;
    aout_FormatPrepare( p_enc_in );

    /* Fix input format */
    p_enc_in->i_format = p_enc->fmt_in.i_codec;
    if( !p_enc_in->i_physical_channels )
    {
        if( p_enc_in->i_channels < ARRAY_SIZE(pi_channels_maps) )
            p_enc_in->i_physical_channels = pi_channels_maps[p_enc_in->i_channels];
    }
    aout_FormatPrepare( p_enc_in );

    return VLC_SUCCESS;
}