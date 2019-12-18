#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ audio_output_t ;
struct TYPE_8__ {int mute; int /*<<< orphan*/  mb; } ;
struct TYPE_7__ {int /*<<< orphan*/ * p_dsbuffer; } ;
struct TYPE_10__ {TYPE_2__ volume; TYPE_1__ s; } ;
typedef  TYPE_4__ aout_sys_t ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSBVOLUME_MIN ; 
 scalar_t__ DS_OK ; 
 scalar_t__ IDirectSoundBuffer_SetVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_MuteReport (TYPE_3__*,int) ; 

__attribute__((used)) static int MuteSet( audio_output_t *p_aout, bool mute )
{
    HRESULT res = DS_OK;
    aout_sys_t *sys = p_aout->sys;

    sys->volume.mute = mute;

    if( sys->s.p_dsbuffer != NULL )
        res = IDirectSoundBuffer_SetVolume( sys->s.p_dsbuffer,
                                            mute? DSBVOLUME_MIN : sys->volume.mb );

    aout_MuteReport( p_aout, mute );
    return (res != DS_OK);
}