#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_16__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_17__ {double frame_rate_den; int frame_rate_num; int /*<<< orphan*/  dts; TYPE_7__* p_packetizer; int /*<<< orphan*/ * p_es; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_18__ {scalar_t__ i_dts; int i_flags; scalar_t__ i_length; int /*<<< orphan*/  i_pts; struct TYPE_18__* p_next; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_15__ {double i_frame_rate_base; int i_frame_rate; } ;
struct TYPE_14__ {int b_packetized; TYPE_1__ video; } ;
struct TYPE_19__ {TYPE_11__ fmt_out; TYPE_4__* (* pf_packetize ) (TYPE_7__*,TYPE_4__**) ;} ;

/* Variables and functions */
 int BLOCK_FLAG_TYPE_MASK ; 
 double CLOCK_FREQ ; 
 int /*<<< orphan*/  H26X_PACKET_SIZE ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_4__*) ; 
 int /*<<< orphan*/  date_Change (int /*<<< orphan*/ *,int,double) ; 
 void* date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Increment (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__ const) ; 
 int /*<<< orphan*/ * es_out_Add (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,double) ; 
 unsigned int round (double) ; 
 TYPE_4__* stub1 (TYPE_7__*,TYPE_4__**) ; 
 TYPE_4__* vlc_stream_Block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux( demux_t *p_demux)
{
    demux_sys_t *p_sys = p_demux->p_sys;
    block_t *p_block_in, *p_block_out;
    bool b_eof = false;

    p_block_in = vlc_stream_Block( p_demux->s, H26X_PACKET_SIZE );
    if( p_block_in == NULL )
    {
        b_eof = true;
    }
    else
    {
        p_block_in->i_dts = date_Get( &p_sys->dts );
    }

    while( (p_block_out = p_sys->p_packetizer->pf_packetize( p_sys->p_packetizer,
                                                             p_block_in ? &p_block_in : NULL )) )
    {
        while( p_block_out )
        {
            block_t *p_next = p_block_out->p_next;

            p_block_out->p_next = NULL;

            if( p_block_in )
            {
                p_block_in->i_dts = date_Get( &p_sys->dts );
                p_block_in->i_pts = VLC_TICK_INVALID;
            }

            if( p_sys->p_es == NULL )
            {
                p_sys->p_packetizer->fmt_out.b_packetized = true;
                p_sys->p_es = es_out_Add( p_demux->out, &p_sys->p_packetizer->fmt_out );
                if( !p_sys->p_es )
                {
                    block_ChainRelease( p_block_out );
                    return VLC_DEMUXER_EOF;
                }
            }

            /* h264 packetizer does merge multiple NAL into AU, but slice flag persists */
            bool frame = p_block_out->i_flags & BLOCK_FLAG_TYPE_MASK;
            const vlc_tick_t i_frame_dts = p_block_out->i_dts;
            const vlc_tick_t i_frame_length = p_block_out->i_length;
            es_out_Send( p_demux->out, p_sys->p_es, p_block_out );
            if( frame )
            {
                if( p_sys->p_packetizer->fmt_out.video.i_frame_rate_base &&
                    p_sys->p_packetizer->fmt_out.video.i_frame_rate_base != p_sys->frame_rate_den &&
                    p_sys->p_packetizer->fmt_out.video.i_frame_rate &&
                    p_sys->p_packetizer->fmt_out.video.i_frame_rate_base != p_sys->frame_rate_num )
                {
                    p_sys->frame_rate_num = p_sys->p_packetizer->fmt_out.video.i_frame_rate;
                    p_sys->frame_rate_den = p_sys->p_packetizer->fmt_out.video.i_frame_rate_base;
                    date_Change( &p_sys->dts, 2 * p_sys->frame_rate_num, p_sys->frame_rate_den );
                    msg_Dbg( p_demux, "using %.2f fps", (double) p_sys->frame_rate_num / p_sys->frame_rate_den );
                }

                es_out_SetPCR( p_demux->out, date_Get( &p_sys->dts ) );
                unsigned i_nb_fields;
                if( i_frame_length > 0 )
                {
                    i_nb_fields = round( (double)i_frame_length * 2 * p_sys->frame_rate_num /
                                  ( p_sys->frame_rate_den * CLOCK_FREQ ) );
                }
                else i_nb_fields = 2;
                if( i_nb_fields <= 6 ) /* in the legit range */
                    date_Increment( &p_sys->dts, i_nb_fields );
                else /* Somehow some discontinuity */
                    date_Set( &p_sys->dts, i_frame_dts );
            }

            p_block_out = p_next;
        }
    }
    return (b_eof) ? VLC_DEMUXER_EOF : VLC_DEMUXER_SUCCESS;
}