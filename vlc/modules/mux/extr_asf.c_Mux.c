#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_16__ {int /*<<< orphan*/  p_access; TYPE_3__** pp_inputs; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_17__ {int b_write_header; scalar_t__ i_dts_last; scalar_t__ i_dts_first; } ;
typedef  TYPE_2__ sout_mux_sys_t ;
struct TYPE_18__ {int /*<<< orphan*/  p_fifo; scalar_t__ p_sys; } ;
typedef  TYPE_3__ sout_input_t ;
struct TYPE_19__ {int i_buffer; int* p_buffer; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_20__ {scalar_t__ i_fourcc; } ;
typedef  TYPE_5__ asf_track_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_HEADER ; 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 TYPE_4__* asf_header_create (TYPE_1__*,int) ; 
 TYPE_4__* asf_packet_create (TYPE_1__*,TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* block_FifoGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sout_AccessOutWrite (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int sout_MuxGetStream (TYPE_1__*,int,scalar_t__*) ; 

__attribute__((used)) static int Mux( sout_mux_t *p_mux )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;

    if( p_sys->b_write_header )
    {
        block_t *out = asf_header_create( p_mux, true );

        out->i_flags |= BLOCK_FLAG_HEADER;
        sout_AccessOutWrite( p_mux->p_access, out );

        p_sys->b_write_header = false;
    }

    for( ;; )
    {
        sout_input_t  *p_input;
        asf_track_t   *tk;
        vlc_tick_t    i_dts;
        block_t *data;
        block_t *pk;

        int i_stream = sout_MuxGetStream( p_mux, 1, &i_dts );
        if( i_stream < 0 )
        {
            /* not enough data */
            return VLC_SUCCESS;
        }

        if( p_sys->i_dts_first == VLC_TICK_INVALID )
        {
            p_sys->i_dts_first = i_dts;
        }
        if( p_sys->i_dts_last < i_dts )
        {
            p_sys->i_dts_last = i_dts;
        }

        p_input = p_mux->pp_inputs[i_stream];
        tk      = (asf_track_t*)p_input->p_sys;

        data = block_FifoGet( p_input->p_fifo );

        /* Convert VC1 to ASF special format */
        if( tk->i_fourcc == VLC_FOURCC( 'W', 'V', 'C', '1' ) )
        {
            while( data->i_buffer >= 4 &&
                   ( data->p_buffer[0] != 0x00 || data->p_buffer[1] != 0x00 ||
                     data->p_buffer[2] != 0x01 ||
                     ( data->p_buffer[3] != 0x0D && data->p_buffer[3] != 0x0C ) ) )
            {
                data->i_buffer--;
                data->p_buffer++;
            }
            if( data->i_buffer >= 4 )
            {
                data->i_buffer -= 4;
                data->p_buffer += 4;
            }
        }

        if( ( pk = asf_packet_create( p_mux, tk, data ) ) )
        {
            sout_AccessOutWrite( p_mux->p_access, pk );
        }
    }

    return VLC_SUCCESS;
}