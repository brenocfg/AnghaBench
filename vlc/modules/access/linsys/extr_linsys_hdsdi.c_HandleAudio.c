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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_8__ {int i_channel; int /*<<< orphan*/ * p_es; int /*<<< orphan*/  i_delay; } ;
typedef  TYPE_1__ hdsdi_audio_t ;
struct TYPE_9__ {int /*<<< orphan*/  out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_10__ {int i_ablock_size; scalar_t__ i_aincr; scalar_t__ i_next_adate; int /*<<< orphan*/  i_sample_rate; scalar_t__ i_max_channel; TYPE_1__* p_audios; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_11__ {scalar_t__ i_length; scalar_t__ i_pts; scalar_t__ i_dts; scalar_t__ p_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int MAX_AUDIOS ; 
 int /*<<< orphan*/  SparseCopy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,scalar_t__) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_4__* block_Alloc (int) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_tick_from_samples (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int HandleAudio( demux_t *p_demux, const uint8_t *p_buffer )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    for ( int i = 0; i < MAX_AUDIOS; i++ )
    {
        hdsdi_audio_t *p_audio = &p_sys->p_audios[i];
        if ( p_audio->i_channel != -1 && p_audio->p_es != NULL )
        {
            block_t *p_block = block_Alloc( p_sys->i_ablock_size );
            if( unlikely( !p_block ) )
                return VLC_ENOMEM;
            SparseCopy( (int16_t *)p_block->p_buffer, (const int16_t *)p_buffer,
                        p_sys->i_ablock_size / 4,
                        p_audio->i_channel * 2, p_sys->i_max_channel + 1 );

            p_block->i_dts = p_block->i_pts
                = p_sys->i_next_adate + vlc_tick_from_samples(p_audio->i_delay,
                                                              p_sys->i_sample_rate);
            p_block->i_length = p_sys->i_aincr;
            es_out_Send( p_demux->out, p_audio->p_es, p_block );
        }
    }
    p_sys->i_next_adate += p_sys->i_aincr;
    return VLC_SUCCESS;
}