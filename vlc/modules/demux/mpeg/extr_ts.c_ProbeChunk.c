#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_37__ {int i_first; int i_first_dts; } ;
struct TYPE_38__ {int i_pid_pcr; int i_last_dts; int i_number; TYPE_8__ pcr; int /*<<< orphan*/  i_last_dts_byte; } ;
typedef  TYPE_9__ ts_pmt_t ;
struct TYPE_33__ {TYPE_11__* p_pat; TYPE_3__* p_stream; } ;
struct TYPE_25__ {scalar_t__ type; int i_pid; TYPE_4__ u; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_10__ ts_pid_t ;
struct TYPE_36__ {int i_size; TYPE_6__** p_elems; } ;
struct TYPE_26__ {TYPE_7__ programs; } ;
typedef  TYPE_11__ ts_pat_t ;
typedef  int stime_t ;
struct TYPE_27__ {TYPE_13__* p_sys; } ;
typedef  TYPE_12__ demux_t ;
struct TYPE_28__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_13__ demux_sys_t ;
struct TYPE_29__ {scalar_t__ i_size; int* p_buffer; int i_buffer; } ;
typedef  TYPE_14__ block_t ;
struct TYPE_34__ {TYPE_9__* p_pmt; } ;
struct TYPE_35__ {TYPE_5__ u; } ;
struct TYPE_32__ {TYPE_2__* p_es; } ;
struct TYPE_30__ {scalar_t__ i_cat; } ;
struct TYPE_31__ {TYPE_1__ fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_SEEN ; 
 int GetPCR (TYPE_14__*) ; 
 TYPE_10__* GetPID (TYPE_13__*,int const) ; 
 int PIDGet (TYPE_14__*) ; 
 scalar_t__ PIDReferencedByProgram (TYPE_9__*,int) ; 
 int /*<<< orphan*/  PROBE_CHUNK_COUNT ; 
 scalar_t__ ParsePESHeader (int /*<<< orphan*/ ,int*,int,unsigned int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_14__* ReadTSPacket (TYPE_12__*) ; 
 scalar_t__ TS_PACKET_SIZE_188 ; 
 scalar_t__ TYPE_STREAM ; 
 scalar_t__ UNKNOWN_ES ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_12__*) ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ __MIN (int,int) ; 
 int /*<<< orphan*/  block_Release (TYPE_14__*) ; 
 int /*<<< orphan*/  vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ProbeChunk( demux_t *p_demux, int i_program, bool b_end, stime_t *pi_pcr, bool *pb_found )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    int i_count = 0;
    block_t *p_pkt = NULL;

    for( ;; )
    {
        *pi_pcr = -1;

        if( i_count++ > PROBE_CHUNK_COUNT || !( p_pkt = ReadTSPacket( p_demux ) ) )
        {
            break;
        }

        if( p_pkt->i_size < TS_PACKET_SIZE_188 &&
           ( p_pkt->p_buffer[1]&0x80 ) /* transport error */ )
        {
            block_Release( p_pkt );
            continue;
        }

        const int i_pid = PIDGet( p_pkt );
        ts_pid_t *p_pid = GetPID(p_sys, i_pid);

        p_pid->i_flags |= FLAG_SEEN;

        if( i_pid != 0x1FFF && (p_pkt->p_buffer[1] & 0x80) == 0 ) /* not corrupt */
        {
            bool b_pcrresult = true;
            bool b_adaptfield = p_pkt->p_buffer[3] & 0x20;

            if( b_adaptfield && p_pkt->i_buffer >= 4 + 2 + 5 )
                *pi_pcr = GetPCR( p_pkt );

            if( *pi_pcr == -1 &&
                (p_pkt->p_buffer[1] & 0xC0) == 0x40 && /* payload start */
                (p_pkt->p_buffer[3] & 0xD0) == 0x10 && /* Has payload but is not encrypted */
                p_pid->type == TYPE_STREAM &&
                p_pid->u.p_stream->p_es->fmt.i_cat != UNKNOWN_ES
              )
            {
                b_pcrresult = false;
                stime_t i_dts = -1;
                stime_t i_pts = -1;
                uint8_t i_stream_id;
                unsigned i_skip = 4;
                if ( b_adaptfield ) // adaptation field
                    i_skip += 1 + __MIN(p_pkt->p_buffer[4], 182);

                if ( VLC_SUCCESS == ParsePESHeader( VLC_OBJECT(p_demux), &p_pkt->p_buffer[i_skip],
                                                    p_pkt->i_buffer - i_skip, &i_skip,
                                                    &i_dts, &i_pts, &i_stream_id, NULL ) )
                {
                    if( i_dts != -1 )
                        *pi_pcr = i_dts;
                    else if( i_pts != -1 )
                        *pi_pcr = i_pts;
                }
            }

            if( *pi_pcr != -1 )
            {
                ts_pat_t *p_pat = GetPID(p_sys, 0)->u.p_pat;
                for( int i=0; i<p_pat->programs.i_size; i++ )
                {
                    ts_pmt_t *p_pmt = p_pat->programs.p_elems[i]->u.p_pmt;
                    if( p_pmt->i_pid_pcr == p_pid->i_pid ||
                          ( p_pmt->i_pid_pcr == 0x1FFF &&
                            PIDReferencedByProgram( p_pmt, p_pid->i_pid ) )
                      )
                    {
                        if( b_end )
                        {
                            p_pmt->i_last_dts = *pi_pcr;
                            p_pmt->i_last_dts_byte = vlc_stream_Tell( p_sys->stream );
                        }
                        /* Start, only keep first */
                        else if( b_pcrresult && p_pmt->pcr.i_first == -1 )
                        {
                            p_pmt->pcr.i_first = *pi_pcr;
                        }
                        else if( p_pmt->pcr.i_first_dts == -1 )
                        {
                            p_pmt->pcr.i_first_dts = *pi_pcr;
                        }

                        if( i_program == 0 || i_program == p_pmt->i_number )
                            *pb_found = true;
                    }
                }
            }
        }

        block_Release( p_pkt );
    }

    return i_count;
}