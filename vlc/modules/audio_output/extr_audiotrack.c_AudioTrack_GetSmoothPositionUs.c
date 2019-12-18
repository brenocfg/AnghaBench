#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
struct TYPE_12__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ audio_output_t ;
struct TYPE_11__ {scalar_t__ i_last_time; size_t i_idx; int i_count; size_t i_us; int i_latency_us; scalar_t__* p_us; } ;
struct TYPE_13__ {TYPE_3__ smoothpos; } ;
typedef  TYPE_5__ aout_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  STREAM_MUSIC; } ;
struct TYPE_9__ {scalar_t__ getOutputLatency; int /*<<< orphan*/  clazz; } ;
struct TYPE_14__ {TYPE_2__ AudioManager; TYPE_1__ AudioSystem; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  AudioTrack_getPlaybackHeadPosition (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  CallStaticIntMethod ; 
 scalar_t__ FRAMES_TO_US (int /*<<< orphan*/ ) ; 
 int JNI_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SMOOTHPOS_INTERVAL_US ; 
 int SMOOTHPOS_SAMPLE_COUNT ; 
 TYPE_6__ jfields ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static vlc_tick_t
AudioTrack_GetSmoothPositionUs( JNIEnv *env, audio_output_t *p_aout )
{
    aout_sys_t *p_sys = p_aout->sys;
    uint64_t i_audiotrack_us;
    vlc_tick_t i_now = vlc_tick_now();

    /* Fetch an AudioTrack position every SMOOTHPOS_INTERVAL_US (30ms) */
    if( i_now - p_sys->smoothpos.i_last_time >= SMOOTHPOS_INTERVAL_US )
    {
        i_audiotrack_us = FRAMES_TO_US( AudioTrack_getPlaybackHeadPosition( env, p_aout ) );

        p_sys->smoothpos.i_last_time = i_now;

        /* Base the position off the current time */
        p_sys->smoothpos.p_us[p_sys->smoothpos.i_idx] = i_audiotrack_us - i_now;
        p_sys->smoothpos.i_idx = (p_sys->smoothpos.i_idx + 1)
                                 % SMOOTHPOS_SAMPLE_COUNT;
        if( p_sys->smoothpos.i_count < SMOOTHPOS_SAMPLE_COUNT )
            p_sys->smoothpos.i_count++;

        /* Calculate the average position based off the current time */
        p_sys->smoothpos.i_us = 0;
        for( uint32_t i = 0; i < p_sys->smoothpos.i_count; ++i )
            p_sys->smoothpos.i_us += p_sys->smoothpos.p_us[i];
        p_sys->smoothpos.i_us /= p_sys->smoothpos.i_count;

        if( jfields.AudioSystem.getOutputLatency )
        {
            int i_latency_ms = JNI_CALL( CallStaticIntMethod,
                                         jfields.AudioSystem.clazz,
                                         jfields.AudioSystem.getOutputLatency,
                                         jfields.AudioManager.STREAM_MUSIC );

            p_sys->smoothpos.i_latency_us = i_latency_ms > 0 ?
                                            i_latency_ms * 1000L : 0;
        }
    }
    if( p_sys->smoothpos.i_us != 0 )
        return p_sys->smoothpos.i_us + i_now - p_sys->smoothpos.i_latency_us;
    else
        return 0;
}