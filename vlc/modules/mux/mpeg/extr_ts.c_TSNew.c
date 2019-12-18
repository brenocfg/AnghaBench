#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sout_mux_t ;
struct TYPE_13__ {TYPE_4__* p_first; } ;
struct TYPE_10__ {int i_pes_used; scalar_t__ i_pes_dts; scalar_t__ i_pes_length; TYPE_8__ chain_pes; } ;
struct TYPE_9__ {int i_pid; int i_continuity_counter; int b_discontinuity; } ;
struct TYPE_11__ {TYPE_2__ state; TYPE_1__ ts; } ;
typedef  TYPE_3__ sout_input_sys_t ;
struct TYPE_12__ {int i_buffer; int i_flags; int* p_buffer; int i_length; struct TYPE_12__* p_next; scalar_t__ i_dts; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CLOCK ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int BLOCK_FLAG_NO_KEYFRAME ; 
 int BLOCK_FLAG_TYPE_I ; 
 int /*<<< orphan*/  BufferChainGet (TYPE_8__*) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int __MIN (int,int) ; 
 TYPE_4__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static block_t *TSNew( sout_mux_t *p_mux, sout_input_sys_t *p_stream,
                       bool b_pcr )
{
    VLC_UNUSED(p_mux);
    block_t *p_pes = p_stream->state.chain_pes.p_first;

    bool b_new_pes = false;
    bool b_adaptation_field = false;

    int i_payload_max = 184 - ( b_pcr ? 8 : 0 );

    if( p_stream->state.i_pes_used <= 0 )
    {
        b_new_pes = true;
    }
    int i_payload = __MIN( (int)p_pes->i_buffer - p_stream->state.i_pes_used,
                       i_payload_max );

    if( b_pcr || i_payload < i_payload_max )
    {
        b_adaptation_field = true;
    }

    block_t *p_ts = block_Alloc( 188 );

    if (b_new_pes && !(p_pes->i_flags & BLOCK_FLAG_NO_KEYFRAME) && p_pes->i_flags & BLOCK_FLAG_TYPE_I)
    {
        p_ts->i_flags |= BLOCK_FLAG_TYPE_I;
    }

    p_ts->i_dts = p_pes->i_dts;

    p_ts->p_buffer[0] = 0x47;
    p_ts->p_buffer[1] = ( b_new_pes ? 0x40 : 0x00 ) |
        ( ( p_stream->ts.i_pid >> 8 )&0x1f );
    p_ts->p_buffer[2] = p_stream->ts.i_pid & 0xff;
    p_ts->p_buffer[3] = ( b_adaptation_field ? 0x30 : 0x10 ) |
        p_stream->ts.i_continuity_counter;

    p_stream->ts.i_continuity_counter = (p_stream->ts.i_continuity_counter+1)%16;
    p_stream->ts.b_discontinuity = p_pes->i_flags & BLOCK_FLAG_DISCONTINUITY;

    if( b_adaptation_field )
    {
        int i_stuffing = i_payload_max - i_payload;
        if( b_pcr )
        {
            p_ts->i_flags |= BLOCK_FLAG_CLOCK;

            p_ts->p_buffer[4] = 7 + i_stuffing;
            p_ts->p_buffer[5] = 1 << 4; /* PCR_flag */
            if( p_stream->ts.b_discontinuity )
            {
                p_ts->p_buffer[5] |= 0x80; /* flag TS dicontinuity */
                p_stream->ts.b_discontinuity = false;
            }
            memset(&p_ts->p_buffer[12], 0xff, i_stuffing);
        }
        else
        {
            p_ts->p_buffer[4] = --i_stuffing;
            if( i_stuffing-- )
            {
                p_ts->p_buffer[5] = 0;
                memset(&p_ts->p_buffer[6], 0xff, i_stuffing);
            }
        }
    }

    /* copy payload */
    memcpy( &p_ts->p_buffer[188 - i_payload],
            &p_pes->p_buffer[p_stream->state.i_pes_used], i_payload );

    p_stream->state.i_pes_used += i_payload;
    p_stream->state.i_pes_dts = p_pes->i_dts + p_pes->i_length *
        p_stream->state.i_pes_used / p_pes->i_buffer;
    p_stream->state.i_pes_length -= p_pes->i_length * i_payload / p_pes->i_buffer;

    if( p_stream->state.i_pes_used >= (int)p_pes->i_buffer )
    {
        block_Release(BufferChainGet( &p_stream->state.chain_pes ));

        p_pes = p_stream->state.chain_pes.p_first;
        p_stream->state.i_pes_length = 0;
        if( p_pes )
        {
            p_stream->state.i_pes_dts = p_pes->i_dts;
            while( p_pes )
            {
                p_stream->state.i_pes_length += p_pes->i_length;
                p_pes = p_pes->p_next;
            }
        }
        else
        {
            p_stream->state.i_pes_dts = 0;
        }
        p_stream->state.i_pes_used = 0;
    }

    return p_ts;
}