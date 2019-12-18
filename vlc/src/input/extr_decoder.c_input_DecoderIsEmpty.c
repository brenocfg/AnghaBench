#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ i_cat; } ;
struct decoder_owner {int /*<<< orphan*/  lock; scalar_t__ drained; scalar_t__ b_draining; TYPE_1__ fmt; int /*<<< orphan*/ * p_vout; int /*<<< orphan*/ * p_sout_input; int /*<<< orphan*/  p_fifo; int /*<<< orphan*/  b_waiting; } ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  assert (int) ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int sout_InputIsEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_fifo_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_fifo_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int vout_IsEmpty (int /*<<< orphan*/ *) ; 

bool input_DecoderIsEmpty( decoder_t * p_dec )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    assert( !p_owner->b_waiting );

    vlc_fifo_Lock( p_owner->p_fifo );
    if( !vlc_fifo_IsEmpty( p_owner->p_fifo ) || p_owner->b_draining )
    {
        vlc_fifo_Unlock( p_owner->p_fifo );
        return false;
    }
    vlc_fifo_Unlock( p_owner->p_fifo );

    bool b_empty;

    vlc_mutex_lock( &p_owner->lock );
#ifdef ENABLE_SOUT
    if( p_owner->p_sout_input != NULL )
        b_empty = sout_InputIsEmpty( p_owner->p_sout_input );
    else
#endif
    if( p_owner->fmt.i_cat == VIDEO_ES && p_owner->p_vout != NULL )
        b_empty = vout_IsEmpty( p_owner->p_vout );
    else if( p_owner->fmt.i_cat == AUDIO_ES )
        b_empty = !p_owner->b_draining || p_owner->drained;
    else
        b_empty = true; /* TODO subtitles support */
    vlc_mutex_unlock( &p_owner->lock );

    return b_empty;
}