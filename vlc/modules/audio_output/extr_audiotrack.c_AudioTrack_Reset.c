#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_7__ {scalar_t__ i_samples_written; } ;
typedef  TYPE_2__ aout_sys_t ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  AudioTrack_ResetPlaybackHeadPosition (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  AudioTrack_ResetPositions (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
AudioTrack_Reset( JNIEnv *env, audio_output_t *p_aout )
{
    aout_sys_t *p_sys = p_aout->sys;

    AudioTrack_ResetPositions( env, p_aout );
    AudioTrack_ResetPlaybackHeadPosition( env, p_aout );
    p_sys->i_samples_written = 0;
}