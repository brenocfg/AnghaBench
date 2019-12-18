#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  scalar_t__ jlong ;
struct TYPE_8__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ audio_output_t ;
struct TYPE_7__ {scalar_t__ i_last_time; scalar_t__ i_frame_us; scalar_t__ i_frame_pos; scalar_t__ i_play_time; int /*<<< orphan*/  p_obj; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_rate; } ;
struct TYPE_9__ {TYPE_2__ timestamp; TYPE_1__ fmt; } ;
typedef  TYPE_4__ aout_sys_t ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 scalar_t__ AUDIOTIMESTAMP_INTERVAL_US ; 
 scalar_t__ FRAMES_TO_US (scalar_t__) ; 
 scalar_t__ JNI_AT_CALL_BOOL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ JNI_AUDIOTIMESTAMP_GET_LONG (int /*<<< orphan*/ ) ; 
 scalar_t__ VLC_TICK_FROM_NS (scalar_t__) ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  framePosition ; 
 int /*<<< orphan*/  getTimestamp ; 
 int /*<<< orphan*/  nanoTime ; 
 scalar_t__ samples_from_vlc_tick (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static vlc_tick_t
AudioTrack_GetTimestampPositionUs( JNIEnv *env, audio_output_t *p_aout )
{
    aout_sys_t *p_sys = p_aout->sys;
    vlc_tick_t i_now;

    if( !p_sys->timestamp.p_obj )
        return 0;

    i_now = vlc_tick_now();

    /* Android doc:
     * getTimestamp: Poll for a timestamp on demand.
     *
     * If you need to track timestamps during initial warmup or after a
     * routing or mode change, you should request a new timestamp once per
     * second until the reported timestamps show that the audio clock is
     * stable. Thereafter, query for a new timestamp approximately once
     * every 10 seconds to once per minute. Calling this method more often
     * is inefficient. It is also counter-productive to call this method
     * more often than recommended, because the short-term differences
     * between successive timestamp reports are not meaningful. If you need
     * a high-resolution mapping between frame position and presentation
     * time, consider implementing that at application level, based on
     * low-resolution timestamps.
     */

    /* Fetch an AudioTrack timestamp every AUDIOTIMESTAMP_INTERVAL_US (500ms) */
    if( i_now - p_sys->timestamp.i_last_time >= AUDIOTIMESTAMP_INTERVAL_US )
    {
        p_sys->timestamp.i_last_time = i_now;

        if( JNI_AT_CALL_BOOL( getTimestamp, p_sys->timestamp.p_obj ) )
        {
            p_sys->timestamp.i_frame_us = VLC_TICK_FROM_NS(JNI_AUDIOTIMESTAMP_GET_LONG( nanoTime ));
            p_sys->timestamp.i_frame_pos = JNI_AUDIOTIMESTAMP_GET_LONG( framePosition );
        }
        else
        {
            p_sys->timestamp.i_frame_us = 0;
            p_sys->timestamp.i_frame_pos = 0;
        }
    }

    /* frame time should be after last play time
     * frame time shouldn't be in the future
     * frame time should be less than 10 seconds old */
    if( p_sys->timestamp.i_frame_us != 0 && p_sys->timestamp.i_frame_pos != 0
     && p_sys->timestamp.i_frame_us > p_sys->timestamp.i_play_time
     && i_now > p_sys->timestamp.i_frame_us
     && ( i_now - p_sys->timestamp.i_frame_us ) <= VLC_TICK_FROM_SEC(10) )
    {
        vlc_tick_t i_time_diff = i_now - p_sys->timestamp.i_frame_us;
        jlong i_frames_diff = samples_from_vlc_tick(i_time_diff, p_sys->fmt.i_rate);
        return FRAMES_TO_US( p_sys->timestamp.i_frame_pos + i_frames_diff );
    } else
        return 0;
}