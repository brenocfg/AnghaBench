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
struct TYPE_15__ {scalar_t__ i_data_size; scalar_t__ i_gathered; TYPE_5__* p_data; TYPE_5__** pp_last; } ;
struct TYPE_16__ {TYPE_2__ gather; } ;
typedef  TYPE_3__ ts_stream_t ;
struct TYPE_14__ {TYPE_3__* p_stream; } ;
struct TYPE_17__ {TYPE_1__ u; } ;
typedef  TYPE_4__ ts_pid_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_18__ {scalar_t__ i_buffer; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ParsePESDataChain (int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 int /*<<< orphan*/  block_ChainLastAppend (TYPE_5__***,TYPE_5__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_5__*) ; 

__attribute__((used)) static bool PushPESBlock( demux_t *p_demux, ts_pid_t *pid, block_t *p_pkt, bool b_unit_start )
{
    bool b_ret = false;
    ts_stream_t *p_pes = pid->u.p_stream;

    if ( b_unit_start && p_pes->gather.p_data )
    {
        block_t *p_datachain = p_pes->gather.p_data;
        /* Flush the pes from pid */
        p_pes->gather.p_data = NULL;
        p_pes->gather.i_data_size = 0;
        p_pes->gather.i_gathered = 0;
        p_pes->gather.pp_last = &p_pes->gather.p_data;
        ParsePESDataChain( p_demux, pid, p_datachain );
        b_ret = true;
    }

    if( p_pkt == NULL )
        return b_ret;

    if( !b_unit_start && p_pes->gather.p_data == NULL )
    {
        /* msg_Dbg( p_demux, "broken packet" ); */
        block_Release( p_pkt );
        return b_ret;
    }

    block_ChainLastAppend( &p_pes->gather.pp_last, p_pkt );
    p_pes->gather.i_gathered += p_pkt->i_buffer;

    if( p_pes->gather.i_data_size > 0 &&
        p_pes->gather.i_gathered >= p_pes->gather.i_data_size )
    {
        /* re-enter in Flush above */
        assert(p_pes->gather.p_data);
        return PushPESBlock( p_demux, pid, NULL, true );
    }

    return b_ret;
}