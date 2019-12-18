#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float i_left_samples; float i_right_samples; int i_nb_samples; int /*<<< orphan*/  p_es; int /*<<< orphan*/ * p_buffer; int /*<<< orphan*/  i_rate; int /*<<< orphan*/  i_delay; int /*<<< orphan*/  i_pair; int /*<<< orphan*/  i_group; } ;
typedef  TYPE_1__ sdi_audio_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_11__ {int /*<<< orphan*/  out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_12__ {scalar_t__ i_next_date; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_13__ {scalar_t__ p_buffer; scalar_t__ i_pts; scalar_t__ i_dts; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ResampleAudio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,float) ; 
 float SAMPLERATE_TOLERANCE ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_4__* block_Alloc (int) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_tick_from_samples (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DecodeAudio( demux_t *p_demux, sdi_audio_t *p_audio )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    block_t *p_block;
    int16_t *p_output;

    if ( p_audio->p_buffer == NULL )
        return VLC_EGENERIC;
    if ( !p_audio->i_left_samples && !p_audio->i_right_samples )
    {
        msg_Warn( p_demux, "no audio %u/%u", p_audio->i_group,
                  p_audio->i_pair );
        return VLC_EGENERIC;
    }
    if ( p_audio->i_left_samples <
            (float)p_audio->i_nb_samples * (1.f - SAMPLERATE_TOLERANCE) ||
        p_audio->i_left_samples >
            (float)p_audio->i_nb_samples * (1.f + SAMPLERATE_TOLERANCE) )
    {
        msg_Warn( p_demux,
            "left samplerate out of tolerance for audio %u/%u (%u vs. %u)",
            p_audio->i_group, p_audio->i_pair,
            p_audio->i_left_samples, p_audio->i_nb_samples );
        return VLC_EGENERIC;
    }
    if ( p_audio->i_right_samples <
            (float)p_audio->i_nb_samples * (1.f - SAMPLERATE_TOLERANCE) ||
        p_audio->i_right_samples >
            (float)p_audio->i_nb_samples * (1.f + SAMPLERATE_TOLERANCE) )
    {
        msg_Warn( p_demux,
            "right samplerate out of tolerance for audio %u/%u (%u vs. %u)",
            p_audio->i_group, p_audio->i_pair,
            p_audio->i_right_samples, p_audio->i_nb_samples );
        return VLC_EGENERIC;
    }

    p_block = block_Alloc( p_audio->i_nb_samples * sizeof(int16_t) * 2 );
    if( unlikely( !p_block ) )
        return VLC_ENOMEM;
    p_block->i_dts = p_block->i_pts = p_sys->i_next_date
        + vlc_tick_from_samples(p_audio->i_delay, p_audio->i_rate);
    p_output = (int16_t *)p_block->p_buffer;

    if ( p_audio->i_left_samples == p_audio->i_nb_samples &&
         p_audio->i_right_samples == p_audio->i_nb_samples )
        memcpy( p_output, p_audio->p_buffer,
                    p_audio->i_nb_samples * sizeof(int16_t) * 2 );
    else
    {
        ResampleAudio( p_output, p_audio->p_buffer,
                       p_audio->i_nb_samples, p_audio->i_left_samples );

        ResampleAudio( p_output + 1, p_audio->p_buffer + 1,
                       p_audio->i_nb_samples, p_audio->i_right_samples );
    }

    es_out_Send( p_demux->out, p_audio->p_es, p_block );
    return VLC_SUCCESS;
}