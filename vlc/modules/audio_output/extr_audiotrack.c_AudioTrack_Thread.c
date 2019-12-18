#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_14__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ audio_output_t ;
struct TYPE_11__ {int /*<<< orphan*/ * p_obj; } ;
struct TYPE_12__ {TYPE_1__ bytebuffer; } ;
struct TYPE_13__ {size_t i_read; size_t i_write; size_t i_size; TYPE_2__ u; } ;
struct TYPE_15__ {int b_thread_waiting; int i_max_audiotrack_samples; scalar_t__ i_write_type; TYPE_3__ circular; int /*<<< orphan*/  lock; int /*<<< orphan*/  aout_cond; scalar_t__ b_error; scalar_t__ b_thread_running; int /*<<< orphan*/  thread_cond; scalar_t__ b_thread_paused; } ;
typedef  TYPE_5__ aout_sys_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_6__**,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_6__* JNIEnv ;

/* Variables and functions */
 int AudioTrack_Play (TYPE_6__**,TYPE_4__*,size_t,size_t,int) ; 
 int FRAMES_TO_US (int) ; 
 TYPE_6__** GET_ENV () ; 
 scalar_t__ WRITE_BYTEARRAY ; 
 scalar_t__ __MAX (int,int) ; 
 size_t __MIN (size_t,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int vlc_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void *
AudioTrack_Thread( void *p_data )
{
    audio_output_t *p_aout = p_data;
    aout_sys_t *p_sys = p_aout->sys;
    JNIEnv *env = GET_ENV();
    vlc_tick_t i_play_deadline = 0;
    vlc_tick_t i_last_time_blocked = 0;

    if( !env )
        return NULL;

    for( ;; )
    {
        int i_ret = 0;
        bool b_forced;
        size_t i_data_offset;
        size_t i_data_size;

        vlc_mutex_lock( &p_sys->lock );

        /* Wait for free space in Audiotrack internal buffer */
        if( i_play_deadline != 0 && vlc_tick_now() < i_play_deadline )
        {
            /* Don't wake up the thread when there is new data since we are
             * waiting for more space */
            p_sys->b_thread_waiting = true;
            while( p_sys->b_thread_running && i_ret == 0 )
                i_ret = vlc_cond_timedwait( &p_sys->thread_cond,
                                            &p_sys->lock,
                                            i_play_deadline );
            i_play_deadline = 0;
            p_sys->b_thread_waiting = false;
        }

        /* Wait for not paused state */
        while( p_sys->b_thread_running && p_sys->b_thread_paused )
        {
            i_last_time_blocked = 0;
            vlc_cond_wait( &p_sys->thread_cond, &p_sys->lock );
        }

        /* Wait for more data in the circular buffer */
        while( p_sys->b_thread_running
            && p_sys->circular.i_read >= p_sys->circular.i_write )
            vlc_cond_wait( &p_sys->thread_cond, &p_sys->lock );

        if( !p_sys->b_thread_running || p_sys->b_error )
        {
            vlc_mutex_unlock( &p_sys->lock );
            break;
        }

        /* HACK: AudioFlinger can drop frames without notifying us and there is
         * no way to know it. If it happens, i_audiotrack_pos won't move and
         * the current code will be stuck because it'll assume that audiotrack
         * internal buffer is full when it's not. It may happen only after
         * Android 4.4.2 if we send frames too quickly. To fix this issue,
         * force the writing of the buffer after a certain delay. */
        if( i_last_time_blocked != 0 )
            b_forced = vlc_tick_now() - i_last_time_blocked >
                       FRAMES_TO_US( p_sys->i_max_audiotrack_samples ) * 2;
        else
            b_forced = false;

        i_data_offset = p_sys->circular.i_read % p_sys->circular.i_size;
        i_data_size = __MIN( p_sys->circular.i_size - i_data_offset,
                             p_sys->circular.i_write - p_sys->circular.i_read );

        i_ret = AudioTrack_Play( env, p_aout, i_data_size, i_data_offset,
                                 b_forced );
        if( i_ret >= 0 )
        {
            if( p_sys->i_write_type == WRITE_BYTEARRAY )
            {
                if( i_ret != 0 )
                    i_last_time_blocked = 0;
                else if( i_last_time_blocked == 0 )
                    i_last_time_blocked = vlc_tick_now();
            }

            if( i_ret == 0 )
                i_play_deadline = vlc_tick_now() + __MAX( 10000, FRAMES_TO_US(
                                  p_sys->i_max_audiotrack_samples / 5 ) );
            else
                p_sys->circular.i_read += i_ret;
        }

        vlc_cond_signal( &p_sys->aout_cond );
        vlc_mutex_unlock( &p_sys->lock );
    }

    if( p_sys->circular.u.bytebuffer.p_obj )
    {
        (*env)->DeleteLocalRef( env, p_sys->circular.u.bytebuffer.p_obj );
        p_sys->circular.u.bytebuffer.p_obj = NULL;
    }

    return NULL;
}