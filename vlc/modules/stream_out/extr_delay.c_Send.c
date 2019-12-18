#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p_next; scalar_t__ p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_8__ {void* id; scalar_t__ i_delay; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
struct TYPE_9__ {scalar_t__ i_pts; scalar_t__ i_dts; struct TYPE_9__* p_next; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 
 int sout_StreamIdSend (int /*<<< orphan*/ ,void*,TYPE_3__*) ; 

__attribute__((used)) static int Send( sout_stream_t *p_stream, void *id, block_t *p_buffer )
{
    sout_stream_sys_t *p_sys = (sout_stream_sys_t *)p_stream->p_sys;

    if ( id == p_sys->id )
    {
        block_t *p_block = p_buffer;
        while ( p_block != NULL )
        {
            if ( p_block->i_pts != VLC_TICK_INVALID )
                p_block->i_pts += p_sys->i_delay;
            if ( p_block->i_dts != VLC_TICK_INVALID )
                p_block->i_dts += p_sys->i_delay;
            p_block = p_block->p_next;
        }
    }

    return sout_StreamIdSend( p_stream->p_next, id, p_buffer );
}