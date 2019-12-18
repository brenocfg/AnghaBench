#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_19__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_21__ {int i_nb_inputs; int /*<<< orphan*/  p_access; TYPE_3__** pp_inputs; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_22__ {int i_pes_count; scalar_t__ i_instant_dts; int i_instant_size; int i_instant_bitrate; int /*<<< orphan*/  i_pes_max_size; int /*<<< orphan*/  b_mpeg2; } ;
typedef  TYPE_2__ sout_mux_sys_t ;
struct TYPE_23__ {TYPE_19__* p_fmt; int /*<<< orphan*/  p_fifo; scalar_t__ p_sys; } ;
typedef  TYPE_3__ sout_input_t ;
struct TYPE_24__ {scalar_t__ i_dts; int /*<<< orphan*/  i_stream_id; } ;
typedef  TYPE_4__ ps_stream_t ;
typedef  int int64_t ;
struct TYPE_25__ {scalar_t__ i_buffer; struct TYPE_25__* p_next; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_5__ block_t ;
struct TYPE_20__ {scalar_t__ i_cat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_HEADER ; 
 int /*<<< orphan*/  EStoPES (TYPE_5__**,TYPE_19__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  MuxWritePSM (TYPE_1__*,TYPE_5__**,scalar_t__) ; 
 int /*<<< orphan*/  MuxWritePackHeader (TYPE_1__*,TYPE_5__**,scalar_t__) ; 
 int /*<<< orphan*/  MuxWriteSystemHeader (TYPE_1__*,TYPE_5__**,scalar_t__) ; 
 scalar_t__ SPU_ES ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  block_ChainAppend (TYPE_5__**,TYPE_5__*) ; 
 TYPE_5__* block_FifoGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sout_AccessOutWrite (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int sout_MuxGetStream (TYPE_1__*,int,scalar_t__*) ; 

__attribute__((used)) static int Mux( sout_mux_t *p_mux )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;

    for( ;; )
    {
        sout_input_t *p_input;
        ps_stream_t *p_stream;

        block_t *p_ps, *p_data;

        vlc_tick_t     i_dts;

        /* Choose which stream to mux */
        int i_stream = sout_MuxGetStream( p_mux, 1, &i_dts );
        if( i_stream < 0 )
        {
            return VLC_SUCCESS;
        }

        p_input  = p_mux->pp_inputs[i_stream];
        p_stream = (ps_stream_t*)p_input->p_sys;
        p_ps     = NULL;

        p_stream->i_dts = i_dts;

        /* Write regulary PackHeader */
        if( p_sys->i_pes_count % 30 == 0)
        {
            vlc_tick_t i_mindts = INT64_MAX;
            for( int i=0; i < p_mux->i_nb_inputs; i++ )
            {
                ps_stream_t *p_s = (ps_stream_t*)p_input->p_sys;
                if( p_input->p_fmt->i_cat == SPU_ES && p_mux->i_nb_inputs > 1 )
                    continue;
                if( p_s->i_dts >= 0 && i_mindts > p_s->i_dts )
                    i_mindts = p_s->i_dts;
            }

            if( i_mindts > p_sys->i_instant_dts )
            {
                /* Update the instant bitrate every second or so */
                if( p_sys->i_instant_size &&
                    i_dts - p_sys->i_instant_dts > VLC_TICK_FROM_SEC(1))
                {
                    int64_t i_instant_bitrate = p_sys->i_instant_size * 8000000 /
                            ( i_dts - p_sys->i_instant_dts );

                    p_sys->i_instant_bitrate += i_instant_bitrate;
                    p_sys->i_instant_bitrate /= 2;

                    p_sys->i_instant_size = 0;
                    p_sys->i_instant_dts = i_dts;
                }
                else if( !p_sys->i_instant_size )
                {
                    p_sys->i_instant_dts = i_dts;
                }

                MuxWritePackHeader( p_mux, &p_ps, i_dts );
            }
        }

        /* Write regulary SystemHeader */
        if( p_sys->i_pes_count % 300 == 0 )
        {
            block_t *p_pk;

            MuxWriteSystemHeader( p_mux, &p_ps, i_dts );

            /* For MPEG1 streaming, set HEADER flag */
            for( p_pk = p_ps; p_pk != NULL; p_pk = p_pk->p_next )
            {
                p_pk->i_flags |= BLOCK_FLAG_HEADER;
            }
        }

        /* Write regulary ProgramStreamMap */
        if( p_sys->b_mpeg2 && p_sys->i_pes_count % 300 == 0 )
        {
            MuxWritePSM( p_mux, &p_ps, i_dts );
        }

        /* Get and mux a packet */
        p_data = block_FifoGet( p_input->p_fifo );
        EStoPES ( &p_data, p_input->p_fmt, p_stream->i_stream_id,
                       p_sys->b_mpeg2, 0, 0, p_sys->i_pes_max_size, 0 );

        block_ChainAppend( &p_ps, p_data );

        /* Get size of output data so we can calculate the instant bitrate */
        for( p_data = p_ps; p_data; p_data = p_data->p_next )
        {
            p_sys->i_instant_size += p_data->i_buffer;
        }

        sout_AccessOutWrite( p_mux->p_access, p_ps );

        /* Increase counter */
        p_sys->i_pes_count++;
    }

    return VLC_SUCCESS;
}