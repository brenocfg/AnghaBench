#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_10__ {float volume; int /*<<< orphan*/ * p_audiotrack; int /*<<< orphan*/  b_error; } ;
typedef  TYPE_3__ aout_sys_t ;
struct TYPE_8__ {scalar_t__ setVolume; } ;
struct TYPE_11__ {TYPE_1__ AudioTrack; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_AT_EXCEPTION (char*) ; 
 int /*<<< orphan*/ * GET_ENV () ; 
 int /*<<< orphan*/  JNI_AT_CALL_INT (int /*<<< orphan*/ ,float,...) ; 
 int /*<<< orphan*/  aout_GainRequest (TYPE_2__*,float) ; 
 int /*<<< orphan*/  aout_VolumeReport (TYPE_2__*,float) ; 
 TYPE_4__ jfields ; 
 int /*<<< orphan*/  setStereoVolume ; 
 int /*<<< orphan*/  setVolume ; 

__attribute__((used)) static int
VolumeSet( audio_output_t *p_aout, float volume )
{
    aout_sys_t *p_sys = p_aout->sys;
    JNIEnv *env;
    float gain = 1.0f;

    if (volume > 1.f)
    {
        p_sys->volume = 1.f;
        gain = volume;
    }
    else
        p_sys->volume = volume;

    if( !p_sys->b_error && p_sys->p_audiotrack != NULL && ( env = GET_ENV() ) )
    {
        if( jfields.AudioTrack.setVolume )
        {
            JNI_AT_CALL_INT( setVolume, volume );
            CHECK_AT_EXCEPTION( "setVolume" );
        } else
        {
            JNI_AT_CALL_INT( setStereoVolume, volume, volume );
            CHECK_AT_EXCEPTION( "setStereoVolume" );
        }
    }
    aout_VolumeReport(p_aout, volume);
    aout_GainRequest(p_aout, gain * gain * gain);
    return 0;
}