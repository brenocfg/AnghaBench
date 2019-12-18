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
struct TYPE_8__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ audio_output_t ;
struct TYPE_7__ {scalar_t__ i_latency_us; scalar_t__ i_us; scalar_t__ i_last_time; scalar_t__ i_idx; scalar_t__ i_count; } ;
struct TYPE_6__ {scalar_t__ i_frame_pos; scalar_t__ i_frame_us; scalar_t__ i_last_time; int /*<<< orphan*/  i_play_time; } ;
struct TYPE_9__ {TYPE_2__ smoothpos; TYPE_1__ timestamp; } ;
typedef  TYPE_4__ aout_sys_t ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static void
AudioTrack_ResetPositions( JNIEnv *env, audio_output_t *p_aout )
{
    aout_sys_t *p_sys = p_aout->sys;
    VLC_UNUSED( env );

    p_sys->timestamp.i_play_time = vlc_tick_now();
    p_sys->timestamp.i_last_time = 0;
    p_sys->timestamp.i_frame_us = 0;
    p_sys->timestamp.i_frame_pos = 0;

    p_sys->smoothpos.i_count = 0;
    p_sys->smoothpos.i_idx = 0;
    p_sys->smoothpos.i_last_time = 0;
    p_sys->smoothpos.i_us = 0;
    p_sys->smoothpos.i_latency_us = 0;
}