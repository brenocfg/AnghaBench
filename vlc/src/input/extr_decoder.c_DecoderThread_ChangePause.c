#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_4__ {int i_cat; } ;
struct TYPE_5__ {TYPE_1__ fmt_out; } ;
struct decoder_owner {int /*<<< orphan*/  lock; int /*<<< orphan*/ * p_aout; int /*<<< orphan*/ * p_vout; TYPE_2__ dec; } ;
typedef  TYPE_2__ decoder_t ;

/* Variables and functions */
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 int /*<<< orphan*/  aout_DecChangePause (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_ChangePause (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DecoderThread_ChangePause( struct decoder_owner *p_owner, bool paused, vlc_tick_t date )
{
    decoder_t *p_dec = &p_owner->dec;

    msg_Dbg( p_dec, "toggling %s", paused ? "resume" : "pause" );
    switch( p_dec->fmt_out.i_cat )
    {
        case VIDEO_ES:
            vlc_mutex_lock( &p_owner->lock );
            if( p_owner->p_vout != NULL )
                vout_ChangePause( p_owner->p_vout, paused, date );
            vlc_mutex_unlock( &p_owner->lock );
            break;
        case AUDIO_ES:
            vlc_mutex_lock( &p_owner->lock );
            if( p_owner->p_aout != NULL )
                aout_DecChangePause( p_owner->p_aout, paused, date );
            vlc_mutex_unlock( &p_owner->lock );
            break;
        case SPU_ES:
            break;
        default:
            vlc_assert_unreachable();
    }
}