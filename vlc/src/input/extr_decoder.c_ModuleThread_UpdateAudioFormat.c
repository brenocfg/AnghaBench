#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ i_format; int i_physical_channels; int /*<<< orphan*/  i_frame_length; int /*<<< orphan*/  i_bytes_per_frame; int /*<<< orphan*/  i_chan_mode; } ;
struct TYPE_16__ {scalar_t__ i_profile; TYPE_5__ audio; int /*<<< orphan*/  audio_replay_gain; } ;
struct decoder_owner {int reset_out_state; int /*<<< orphan*/  p_fifo; TYPE_3__ fmt; int /*<<< orphan*/  lock; int /*<<< orphan*/ * p_aout; int /*<<< orphan*/  p_resource; int /*<<< orphan*/  p_clock; } ;
struct TYPE_15__ {scalar_t__ i_codec; scalar_t__ i_profile; TYPE_5__ audio; int /*<<< orphan*/  audio_replay_gain; } ;
struct TYPE_14__ {int /*<<< orphan*/  audio_replay_gain; } ;
struct TYPE_17__ {TYPE_2__ fmt_out; TYPE_1__ fmt_in; } ;
typedef  TYPE_4__ decoder_t ;
typedef  TYPE_5__ audio_sample_format_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_CHANMODE_DOLBYSTEREO ; 
 int AOUT_CHAN_LEFT ; 
 int AOUT_CHAN_RIGHT ; 
 int /*<<< orphan*/  AOUT_FMTS_IDENTICAL (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  DecoderUpdateFormatLocked (struct decoder_owner*) ; 
 int /*<<< orphan*/  aout_DecDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ aout_DecNew (int /*<<< orphan*/ *,TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_5__*) ; 
 scalar_t__ aout_replaygain_changed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct decoder_owner* dec_get_owner (TYPE_4__*) ; 
 int /*<<< orphan*/ * input_resource_GetAout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_resource_PutAout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*) ; 
 int var_InheritInteger (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  var_TriggerCallback (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ModuleThread_UpdateAudioFormat( decoder_t *p_dec )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    if( p_owner->p_aout &&
       ( !AOUT_FMTS_IDENTICAL(&p_dec->fmt_out.audio, &p_owner->fmt.audio) ||
         p_dec->fmt_out.i_codec != p_dec->fmt_out.audio.i_format ||
         p_dec->fmt_out.i_profile != p_owner->fmt.i_profile ) )
    {
        audio_output_t *p_aout = p_owner->p_aout;

        /* Parameters changed, restart the aout */
        vlc_mutex_lock( &p_owner->lock );
        p_owner->p_aout = NULL; // the DecoderThread should not use the old aout anymore
        vlc_mutex_unlock( &p_owner->lock );
        aout_DecDelete( p_aout );

        input_resource_PutAout( p_owner->p_resource, p_aout );
    }

    /* Check if only replay gain has changed */
    if( aout_replaygain_changed( &p_dec->fmt_in.audio_replay_gain,
                                 &p_owner->fmt.audio_replay_gain ) )
    {
        p_dec->fmt_out.audio_replay_gain = p_dec->fmt_in.audio_replay_gain;
        if( p_owner->p_aout )
        {
            p_owner->fmt.audio_replay_gain = p_dec->fmt_in.audio_replay_gain;
            var_TriggerCallback( p_owner->p_aout, "audio-replay-gain-mode" );
        }
    }

    if( p_owner->p_aout == NULL )
    {
        p_dec->fmt_out.audio.i_format = p_dec->fmt_out.i_codec;

        audio_sample_format_t format = p_dec->fmt_out.audio;
        aout_FormatPrepare( &format );

        const int i_force_dolby = var_InheritInteger( p_dec, "force-dolby-surround" );
        if( i_force_dolby &&
            format.i_physical_channels == (AOUT_CHAN_LEFT|AOUT_CHAN_RIGHT) )
        {
            if( i_force_dolby == 1 )
                format.i_chan_mode |= AOUT_CHANMODE_DOLBYSTEREO;
            else /* i_force_dolby == 2 */
                format.i_chan_mode &= ~AOUT_CHANMODE_DOLBYSTEREO;
        }

        audio_output_t *p_aout;

        p_aout = input_resource_GetAout( p_owner->p_resource );
        if( p_aout )
        {
            if( aout_DecNew( p_aout, &format, p_dec->fmt_out.i_profile,
                             p_owner->p_clock,
                             &p_dec->fmt_out.audio_replay_gain ) )
            {
                input_resource_PutAout( p_owner->p_resource, p_aout );
                p_aout = NULL;
            }
        }

        vlc_mutex_lock( &p_owner->lock );
        p_owner->p_aout = p_aout;

        DecoderUpdateFormatLocked( p_owner );
        aout_FormatPrepare( &p_owner->fmt.audio );
        vlc_mutex_unlock( &p_owner->lock );

        if( p_aout == NULL )
        {
            msg_Err( p_dec, "failed to create audio output" );
            return -1;
        }

        p_dec->fmt_out.audio.i_bytes_per_frame =
            p_owner->fmt.audio.i_bytes_per_frame;
        p_dec->fmt_out.audio.i_frame_length =
            p_owner->fmt.audio.i_frame_length;

        vlc_fifo_Lock( p_owner->p_fifo );
        p_owner->reset_out_state = true;
        vlc_fifo_Unlock( p_owner->p_fifo );
    }
    return 0;
}