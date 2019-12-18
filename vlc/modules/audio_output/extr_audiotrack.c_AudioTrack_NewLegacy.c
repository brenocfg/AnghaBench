#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  jint ;
typedef  int /*<<< orphan*/  audio_output_t ;
struct TYPE_5__ {int /*<<< orphan*/  MODE_STREAM; } ;
struct TYPE_4__ {int /*<<< orphan*/  STREAM_MUSIC; } ;
struct TYPE_6__ {TYPE_2__ AudioTrack; TYPE_1__ AudioManager; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  JNI_AT_NEW (int /*<<< orphan*/ ,unsigned int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_3__ jfields ; 

__attribute__((used)) static jobject
AudioTrack_NewLegacy( JNIEnv *env, audio_output_t *p_aout, unsigned int i_rate,
                      int i_channel_config, int i_format, int i_size,
                      jint session_id )
{
    VLC_UNUSED( p_aout );
    return JNI_AT_NEW( jfields.AudioManager.STREAM_MUSIC, i_rate,
                       i_channel_config, i_format, i_size,
                       jfields.AudioTrack.MODE_STREAM, session_id );
}