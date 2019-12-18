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
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_8__ {scalar_t__ i_delay; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_9__ {scalar_t__ i_buffer; scalar_t__ i_dts; scalar_t__ i_pts; struct TYPE_9__* p_next; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  input_DecoderDecode (int /*<<< orphan*/ *,TYPE_3__*,int) ; 

__attribute__((used)) static int Send( sout_stream_t *p_stream, void *id, block_t *p_buffer )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;

    while( p_buffer )
    {
        block_t *p_next = p_buffer->p_next;

        p_buffer->p_next = NULL;

        if( id != NULL && p_buffer->i_buffer > 0 )
        {
            if( p_buffer->i_dts == VLC_TICK_INVALID )
                p_buffer->i_dts = 0;
            else
                p_buffer->i_dts += p_sys->i_delay;

            if( p_buffer->i_pts == VLC_TICK_INVALID )
                p_buffer->i_pts = 0;
            else
                p_buffer->i_pts += p_sys->i_delay;

            input_DecoderDecode( (decoder_t *)id, p_buffer, false );
        }

        p_buffer = p_next;
    }

    return VLC_SUCCESS;
}