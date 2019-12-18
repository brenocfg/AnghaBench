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
struct TYPE_7__ {int b_flushed; int /*<<< orphan*/  id; TYPE_2__* p_sout; } ;
typedef  TYPE_1__ sout_packetizer_input_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_stream; } ;
typedef  TYPE_2__ sout_instance_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_DISCONTINUITY ; 
 int sout_StreamIdSend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int sout_InputSendBuffer( sout_packetizer_input_t *p_input,
                          block_t *p_buffer )
{
    sout_instance_t     *p_sout = p_input->p_sout;
    int                 i_ret;

    if( p_input->b_flushed )
    {
        p_buffer->i_flags |= BLOCK_FLAG_DISCONTINUITY;
        p_input->b_flushed = false;
    }
    vlc_mutex_lock( &p_sout->lock );
    i_ret = sout_StreamIdSend( p_sout->p_stream, p_input->id, p_buffer );
    vlc_mutex_unlock( &p_sout->lock );

    return i_ret;
}