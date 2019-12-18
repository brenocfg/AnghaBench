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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ encoder_t ;
struct TYPE_5__ {scalar_t__ h; int /*<<< orphan*/  p_sei; int /*<<< orphan*/  psz_stat_name; } ;
typedef  TYPE_2__ encoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,...) ; 
 scalar_t__ pthread_win32_count ; 
 int /*<<< orphan*/  pthread_win32_mutex ; 
 int /*<<< orphan*/  pthread_win32_process_detach_np () ; 
 int /*<<< orphan*/  pthread_win32_thread_detach_np () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x264_encoder_close (scalar_t__) ; 
 int /*<<< orphan*/  x264_encoder_delayed_frames (scalar_t__) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    encoder_t     *p_enc = (encoder_t *)p_this;
    encoder_sys_t *p_sys = p_enc->p_sys;

    free( p_sys->psz_stat_name );
    free( p_sys->p_sei );

    if( p_sys->h )
    {
        msg_Dbg( p_enc, "framecount still in libx264 buffer: %d", x264_encoder_delayed_frames( p_sys->h ) );
        x264_encoder_close( p_sys->h );
    }

#ifdef PTW32_STATIC_LIB
    vlc_mutex_lock( &pthread_win32_mutex );
    pthread_win32_count--;

    if( pthread_win32_count == 0 )
    {
        pthread_win32_thread_detach_np();
        pthread_win32_process_detach_np();
        msg_Dbg( p_enc, "pthread-win32 deinitialized" );
    }

    vlc_mutex_unlock( &pthread_win32_mutex );
#endif
}