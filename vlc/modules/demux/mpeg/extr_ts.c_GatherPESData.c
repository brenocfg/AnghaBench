#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_22__ {int i_saved; scalar_t__ i_data_size; int* saved; scalar_t__ i_gathered; int /*<<< orphan*/ * p_data; } ;
struct TYPE_23__ {int b_broken_PUSI_conformance; TYPE_3__ gather; TYPE_2__* p_es; } ;
typedef  TYPE_4__ ts_stream_t ;
struct TYPE_20__ {TYPE_4__* p_stream; } ;
struct TYPE_24__ {TYPE_1__ u; } ;
typedef  TYPE_5__ ts_pid_t ;
struct TYPE_25__ {TYPE_7__* p_sys; } ;
typedef  TYPE_6__ demux_t ;
struct TYPE_26__ {scalar_t__ b_valid_scrambling; } ;
typedef  TYPE_7__ demux_sys_t ;
struct TYPE_27__ {int* p_buffer; size_t i_buffer; int i_flags; } ;
typedef  TYPE_8__ block_t ;
struct TYPE_21__ {int i_next_block_flags; } ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int BLOCK_FLAG_SCRAMBLED ; 
 int BLOCK_FLAG_SOURCE_RANDOM_ACCESS ; 
 int* FindNextPESHeader (int*,int) ; 
 scalar_t__ GetWBE (int*) ; 
 scalar_t__ MayHaveStartCodeOnEnd (int*,int) ; 
 int PushPESBlock (TYPE_6__*,TYPE_5__*,TYPE_8__*,int const) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_8__* block_Realloc (TYPE_8__*,int,size_t) ; 
 int /*<<< orphan*/  block_Release (TYPE_8__*) ; 
 int /*<<< orphan*/  block_Split (TYPE_8__**,TYPE_8__**,size_t const) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  pes_sync ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool GatherPESData( demux_t *p_demux, ts_pid_t *pid, block_t *p_pkt, size_t i_skip )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    const bool b_unit_start = p_pkt->p_buffer[1]&0x40;
    bool b_ret = false;
    ts_stream_t *p_pes = pid->u.p_stream;

    /* We have to gather it */
    p_pkt->p_buffer += i_skip;
    p_pkt->i_buffer -= i_skip;

    bool b_single_payload = b_unit_start; /* Single payload in case of unit start */
    bool b_aligned_ts_payload = true;

    if( unlikely(p_pes->b_broken_PUSI_conformance) )
    {
        /* Stream does not conform to payload_unit_start flag
         * applied to PES packets (AdTech private_stream_1) */
        b_aligned_ts_payload = false;
        b_single_payload = false;

    }

    /* We'll cannot parse any pes data */
    if( (p_pkt->i_flags & BLOCK_FLAG_SCRAMBLED) && p_sys->b_valid_scrambling )
    {
        block_Release( p_pkt );
        return PushPESBlock( p_demux, pid, NULL, true );
    }

    /* Seek discontinuity, we need to drop or output currently
     * gathered data */
    if( p_pkt->i_flags & BLOCK_FLAG_SOURCE_RANDOM_ACCESS )
    {
        p_pes->gather.i_saved = 0;
        /* Flush/output current */
        b_ret |= PushPESBlock( p_demux, pid, NULL, true );
        /* Propagate to output block to notify packetizers/decoders */
        if( p_pes->p_es )
            p_pes->p_es->i_next_block_flags |= BLOCK_FLAG_DISCONTINUITY;
    }
    /* On dropped blocks discontinuity */
    else if( p_pkt->i_flags & BLOCK_FLAG_DISCONTINUITY )
    {
        /* it can't match the target size and need to resync on sync code */
        p_pes->gather.i_data_size = 0;
        /* can't reuse prev bytes to lookup sync code */
        p_pes->gather.i_saved = 0;
        /* Propagate to output block to notify packetizers/decoders */
        if( p_pes->p_es )
            p_pes->p_es->i_next_block_flags |= BLOCK_FLAG_DISCONTINUITY|BLOCK_FLAG_CORRUPTED;
    }

    if ( unlikely(p_pes->gather.i_saved > 0) )
    {
        /* Saved from previous packet end */
        assert(p_pes->gather.i_saved < 6);
        if( !b_aligned_ts_payload )
        {
            p_pkt = block_Realloc( p_pkt, p_pes->gather.i_saved, p_pkt->i_buffer );
            if( p_pkt )
                memcpy( p_pkt->p_buffer, p_pes->gather.saved, p_pes->gather.i_saved );
        }
        p_pes->gather.i_saved = 0;
    }

    for( bool b_first_sync_done = false; p_pkt; )
    {
        assert( p_pes->gather.i_saved == 0 );

        if( p_pes->gather.p_data == NULL && !b_first_sync_done && p_pkt->i_buffer >= 6 )
        {
            if( likely(b_aligned_ts_payload) )
            {
                if( memcmp( p_pkt->p_buffer, pes_sync, 3 ) )
                {
                    block_Release( p_pkt );
                    return b_ret;
                }
            }
            else
            {
                /* Need to find sync code */
                uint8_t *p_buf = FindNextPESHeader( p_pkt->p_buffer, p_pkt->i_buffer - 3 );
                if( p_buf == NULL )
                {
                    /* no first sync code */
                    if( MayHaveStartCodeOnEnd( p_pkt->p_buffer, p_pkt->i_buffer ) )
                    {
                        /* Drop everything except last bytes for next packet */
                        p_pkt->p_buffer += p_pkt->i_buffer - 3;
                        p_pes->gather.i_saved = p_pkt->i_buffer = 3;
                        memcpy(p_pes->gather.saved, p_pkt->p_buffer, p_pkt->i_buffer);
                    }
                    block_Release( p_pkt );
                    return b_ret;
                }
                p_pkt->i_buffer -= p_buf - p_pkt->p_buffer;
                p_pkt->p_buffer = p_buf;
            }
            /* now points to PES header */
            p_pes->gather.i_data_size = GetWBE(&p_pkt->p_buffer[4]);
            if( p_pes->gather.i_data_size > 0 )
                p_pes->gather.i_data_size += 6;
            b_first_sync_done = true; /* Because if size is 0, we woud not look for second sync */
        }
        else
        {
            assert( p_pes->gather.i_data_size > p_pes->gather.i_gathered ||
                    p_pes->gather.i_data_size == 0 );

            /* If we started reading a fixed size */
            if( p_pes->gather.i_data_size > p_pes->gather.i_gathered )
            {
                const size_t i_remain = p_pes->gather.i_data_size - p_pes->gather.i_gathered;
                /* Append whole block */
                if( likely(p_pkt->i_buffer <= i_remain || b_single_payload) )
                {
                    b_ret |= PushPESBlock( p_demux, pid, p_pkt, p_pes->gather.p_data == NULL );
                    p_pkt = NULL;
                }
                else /* p_pkt->i_buffer > i_remain */
                {
                    block_t *p_split;
                    if( !block_Split( &p_pkt, &p_split, i_remain ) )
                    {
                        block_Release( p_pkt );
                        return false;
                    }
                    b_ret |= PushPESBlock( p_demux, pid, p_pkt, p_pes->gather.p_data == NULL );
                    p_pkt = p_split;
                    b_first_sync_done = false;
                }
            }
            else /* if( p_pes->gather.i_data_size == 0 ) // see next packet */
            {
                /* Append or finish current/start new PES depending on unit_start */
                b_ret |= PushPESBlock( p_demux, pid, p_pkt, b_unit_start );
                p_pkt = NULL;
            }
        }

        if( unlikely(p_pkt && p_pkt->i_buffer < 6) )
        {
            /* save and prepend to next packet */
            assert(!b_single_payload);
            assert(p_pes->gather.i_saved == 0);
            p_pes->gather.i_saved = p_pkt->i_buffer;
            memcpy(p_pes->gather.saved, p_pkt->p_buffer, p_pkt->i_buffer);
            block_Release( p_pkt );
            p_pkt = NULL;
        }
    }

    return b_ret;
}