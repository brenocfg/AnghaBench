#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ audio_output_t ;
struct TYPE_10__ {int /*<<< orphan*/ * p_dsbuffer; } ;
struct TYPE_9__ {float volume; int /*<<< orphan*/  mute; scalar_t__ mb; } ;
struct TYPE_12__ {TYPE_2__ s; TYPE_1__ volume; } ;
typedef  TYPE_4__ aout_sys_t ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 scalar_t__ DSBVOLUME_MAX ; 
 scalar_t__ DSBVOLUME_MIN ; 
 scalar_t__ DS_OK ; 
 scalar_t__ IDirectSoundBuffer_SetVolume (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  __MIN (float,float) ; 
 int /*<<< orphan*/  aout_GainRequest (TYPE_3__*,float) ; 
 int /*<<< orphan*/  aout_VolumeReport (TYPE_3__*,float) ; 
 int /*<<< orphan*/  config_PutFloat (char*,float) ; 
 float log10f (int /*<<< orphan*/ ) ; 
 scalar_t__ lroundf (float) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 scalar_t__ var_InheritBool (TYPE_3__*,char*) ; 

__attribute__((used)) static int VolumeSet( audio_output_t *p_aout, float volume )
{
    aout_sys_t *sys = p_aout->sys;
    int ret = 0;

    /* Directsound doesn't support amplification, so we use software
       gain if we need it and only for this */
    float gain = volume > 1.f ? volume * volume * volume : 1.f;
    aout_GainRequest( p_aout, gain );

    /* millibels from linear amplification */
    LONG mb = lroundf( 6000.f * log10f( __MIN( volume, 1.f ) ));

    /* Clamp to allowed DirectSound range */
    static_assert( DSBVOLUME_MIN < DSBVOLUME_MAX, "DSBVOLUME_* confused" );
    if( mb > DSBVOLUME_MAX )
    {
        mb = DSBVOLUME_MAX;
        ret = -1;
    }
    if( mb <= DSBVOLUME_MIN )
        mb = DSBVOLUME_MIN;

    sys->volume.mb = mb;
    sys->volume.volume = volume;
    if( !sys->volume.mute && sys->s.p_dsbuffer != NULL &&
        IDirectSoundBuffer_SetVolume( sys->s.p_dsbuffer, mb ) != DS_OK )
        return -1;
    /* Convert back to UI volume */
    aout_VolumeReport( p_aout, volume );

    if( var_InheritBool( p_aout, "volume-save" ) )
        config_PutFloat( "directx-volume", volume );
    return ret;
}