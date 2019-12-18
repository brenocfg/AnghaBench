#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct decoder_owner {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_acknowledge; int /*<<< orphan*/  p_fifo; scalar_t__ b_idle; scalar_t__ paused; int /*<<< orphan*/  b_has_data; int /*<<< orphan*/  b_waiting; } ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_fifo_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_DecoderWait( decoder_t *p_dec )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    assert( p_owner->b_waiting );

    vlc_mutex_lock( &p_owner->lock );
    while( !p_owner->b_has_data )
    {
        /* Don't need to lock p_owner->paused since it's only modified by the
         * owner */
        if( p_owner->paused )
            break;
        vlc_fifo_Lock( p_owner->p_fifo );
        if( p_owner->b_idle && vlc_fifo_IsEmpty( p_owner->p_fifo ) )
        {
            msg_Err( p_dec, "buffer deadlock prevented" );
            vlc_fifo_Unlock( p_owner->p_fifo );
            break;
        }
        vlc_fifo_Unlock( p_owner->p_fifo );
        vlc_cond_wait( &p_owner->wait_acknowledge, &p_owner->lock );
    }
    vlc_mutex_unlock( &p_owner->lock );
}