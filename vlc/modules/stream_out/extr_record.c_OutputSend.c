#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_13__ {scalar_t__ i_dts_start; size_t i_size; scalar_t__ b_drop; int /*<<< orphan*/  p_out; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
struct TYPE_14__ {int b_wait_key; int b_wait_start; int /*<<< orphan*/  pp_last; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;
struct TYPE_15__ {int i_flags; scalar_t__ i_dts; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_TYPE_I ; 
 int BLOCK_FLAG_TYPE_MASK ; 
 int /*<<< orphan*/  block_ChainLastAppend (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  block_ChainProperties (TYPE_4__*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_4__*) ; 
 int /*<<< orphan*/  sout_StreamIdSend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void OutputSend( sout_stream_t *p_stream, sout_stream_id_sys_t *id, block_t *p_block )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;

    if( id->id )
    {
        /* We wait until the first key frame (if needed) and
         * to be beyong i_dts_start (for stream without key frame) */
        if( unlikely( id->b_wait_key ) )
        {
            if( p_block->i_flags & BLOCK_FLAG_TYPE_I )
            {
                id->b_wait_key = false;
                id->b_wait_start = false;
            }

            if( ( p_block->i_flags & BLOCK_FLAG_TYPE_MASK ) == 0 )
                id->b_wait_key = false;
        }
        if( unlikely( id->b_wait_start ) )
        {
            if( p_block->i_dts >=p_sys->i_dts_start )
                id->b_wait_start = false;
        }
        if( unlikely( id->b_wait_key || id->b_wait_start ) )
            block_ChainRelease( p_block );
        else
            sout_StreamIdSend( p_sys->p_out, id->id, p_block );
    }
    else if( p_sys->b_drop )
    {
        block_ChainRelease( p_block );
    }
    else
    {
        size_t i_size;

        block_ChainProperties( p_block, NULL, &i_size, NULL );
        p_sys->i_size += i_size;
        block_ChainLastAppend( &id->pp_last, p_block );
    }
}