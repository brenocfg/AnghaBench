#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_6__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_5__ {int i_last; scalar_t__ i_wrap_count; } ;
struct TYPE_7__ {TYPE_1__ headpos; } ;
typedef  TYPE_3__ aout_sys_t ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int JNI_AT_CALL_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getPlaybackHeadPosition ; 

__attribute__((used)) static uint64_t
AudioTrack_getPlaybackHeadPosition( JNIEnv *env, audio_output_t *p_aout )
{
    /* Android doc:
     * getPlaybackHeadPosition: Returns the playback head position expressed in
     * frames. Though the "int" type is signed 32-bits, the value should be
     * reinterpreted as if it is unsigned 32-bits. That is, the next position
     * after 0x7FFFFFFF is (int) 0x80000000. This is a continuously advancing
     * counter. It will wrap (overflow) periodically, for example approximately
     * once every 27:03:11 hours:minutes:seconds at 44.1 kHz. It is reset to
     * zero by flush(), reload(), and stop().
     */

    aout_sys_t *p_sys = p_aout->sys;
    uint32_t i_pos;

    /* int32_t to uint32_t */
    i_pos = 0xFFFFFFFFL & JNI_AT_CALL_INT( getPlaybackHeadPosition );

    /* uint32_t to uint64_t */
    if( p_sys->headpos.i_last > i_pos )
        p_sys->headpos.i_wrap_count++;
    p_sys->headpos.i_last = i_pos;
    return p_sys->headpos.i_last + ((uint64_t)p_sys->headpos.i_wrap_count << 32);
}