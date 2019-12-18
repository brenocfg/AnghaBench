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
struct TYPE_11__ {int /*<<< orphan*/  out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_10__ {int channels; int /*<<< orphan*/  sample_freq; } ;
struct TYPE_12__ {int i_position; int /*<<< orphan*/  p_es; TYPE_1__ info; int /*<<< orphan*/  decoder; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_13__ {int i_buffer; scalar_t__ i_dts; scalar_t__ i_pts; scalar_t__ p_buffer; } ;
typedef  TYPE_4__ block_t ;
typedef  int /*<<< orphan*/  MPC_SAMPLE_FORMAT ;

/* Variables and functions */
 int MPC_DECODER_BUFFER_LENGTH ; 
 int VLC_DEMUXER_EGENERIC ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 TYPE_4__* block_New (TYPE_2__*,int) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 int mpc_decoder_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_tick_from_samples (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    block_t     *p_data;
    int i_ret;

    p_data = block_New( p_demux,
                        MPC_DECODER_BUFFER_LENGTH*sizeof(MPC_SAMPLE_FORMAT) );
    if( !p_data )
        return VLC_DEMUXER_EGENERIC;

    i_ret = mpc_decoder_decode( &p_sys->decoder,
                                (MPC_SAMPLE_FORMAT*)p_data->p_buffer,
                                NULL, NULL );
    if( i_ret <= 0 )
    {
        block_Release( p_data );
        return i_ret < 0 ? VLC_DEMUXER_EGENERIC : VLC_DEMUXER_EOF;
    }

    /* */
    p_data->i_buffer = i_ret * sizeof(MPC_SAMPLE_FORMAT) * p_sys->info.channels;
    p_data->i_dts = p_data->i_pts =
            VLC_TICK_0 + vlc_tick_from_samples(p_sys->i_position, p_sys->info.sample_freq);

    es_out_SetPCR( p_demux->out, p_data->i_dts );

    es_out_Send( p_demux->out, p_sys->p_es, p_data );

    /* */
    p_sys->i_position += i_ret;

    return VLC_DEMUXER_SUCCESS;
}