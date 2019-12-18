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
struct TYPE_7__ {int /*<<< orphan*/ * client; } ;
typedef  TYPE_2__ aout_sys_t ;
typedef  int /*<<< orphan*/  ISimpleAudioVolume ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAudioClient_GetService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_ISimpleAudioVolume ; 
 int /*<<< orphan*/  ISimpleAudioVolume_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISimpleAudioVolume_SetMasterVolume (int /*<<< orphan*/ *,float,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  aout_GainRequest (TYPE_1__*,float) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int VolumeSet(audio_output_t *aout, float vol)
{
    aout_sys_t *sys = aout->sys;
    if( unlikely( sys->client == NULL ) )
        return VLC_EGENERIC;
    HRESULT hr;
    ISimpleAudioVolume *pc_AudioVolume = NULL;
    float gain = 1.f;

    vol = vol * vol * vol; /* ISimpleAudioVolume is tapered linearly. */

    if (vol > 1.f)
    {
        gain = vol;
        vol = 1.f;
    }

    aout_GainRequest(aout, gain);

    hr = IAudioClient_GetService(sys->client, &IID_ISimpleAudioVolume, &pc_AudioVolume);
    if (FAILED(hr))
    {
        msg_Err(aout, "cannot get volume service (error 0x%lX)", hr);
        goto done;
    }

    hr = ISimpleAudioVolume_SetMasterVolume(pc_AudioVolume, vol, NULL);
    if (FAILED(hr))
    {
        msg_Err(aout, "cannot set volume (error 0x%lX)", hr);
        goto done;
    }

done:
    ISimpleAudioVolume_Release(pc_AudioVolume);

    return SUCCEEDED(hr) ? 0 : -1;
}