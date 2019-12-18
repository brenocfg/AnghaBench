#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_6__ {int b_thread_paused; int /*<<< orphan*/  lock; scalar_t__ b_error; } ;
typedef  TYPE_2__ aout_sys_t ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  AudioTrack_ResetPositions (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CHECK_AT_EXCEPTION (char*) ; 
 int /*<<< orphan*/ * GET_ENV () ; 
 int /*<<< orphan*/  JNI_AT_CALL_VOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause ; 
 int /*<<< orphan*/  play ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Pause( audio_output_t *p_aout, bool b_pause, vlc_tick_t i_date )
{
    aout_sys_t *p_sys = p_aout->sys;
    JNIEnv *env;
    VLC_UNUSED( i_date );

    vlc_mutex_lock( &p_sys->lock );

    if( p_sys->b_error || !( env = GET_ENV() ) )
        goto bailout;

    if( b_pause )
    {
        p_sys->b_thread_paused = true;
        JNI_AT_CALL_VOID( pause );
        CHECK_AT_EXCEPTION( "pause" );
    } else
    {
        p_sys->b_thread_paused = false;
        AudioTrack_ResetPositions( env, p_aout );
        JNI_AT_CALL_VOID( play );
        CHECK_AT_EXCEPTION( "play" );
    }

bailout:
    vlc_mutex_unlock( &p_sys->lock );
}