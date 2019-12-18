#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
typedef  int /*<<< orphan*/  ISimpleAudioVolume ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  float HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  AUDCLNT_STREAMFLAGS_NOPERSIST ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 float E_INVALIDARG ; 
 scalar_t__ FALSE ; 
 float IAudioClient_GetMixFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 float IAudioClient_GetService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 float IAudioClient_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  IID_ISimpleAudioVolume ; 
 float IMMDevice_Activate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 float ISimpleAudioVolume_GetMasterVolume (int /*<<< orphan*/ *,float*) ; 
 float ISimpleAudioVolume_GetMute (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ISimpleAudioVolume_Release (int /*<<< orphan*/ *) ; 
 float ISimpleAudioVolume_SetMasterVolume (int /*<<< orphan*/ *,float,int /*<<< orphan*/ *) ; 
 float ISimpleAudioVolume_SetMute (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 float NULL_PTR_ERR ; 
 float S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  dev ; 
 float fabsf (float) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_simplevolume(void)
{
    IAudioClient *ac;
    ISimpleAudioVolume *sav;
    WAVEFORMATEX *fmt;
    HRESULT hr;
    float vol;
    BOOL mute;

    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &fmt);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED,
            AUDCLNT_STREAMFLAGS_NOPERSIST, 5000000, 0, fmt, NULL);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);

    if(hr == S_OK){
        hr = IAudioClient_GetService(ac, &IID_ISimpleAudioVolume, (void**)&sav);
        ok(hr == S_OK, "GetService failed: %08x\n", hr);
    }
    if(hr != S_OK){
        IAudioClient_Release(ac);
        CoTaskMemFree(fmt);
        return;
    }

    hr = ISimpleAudioVolume_GetMasterVolume(sav, NULL);
    ok(hr == NULL_PTR_ERR, "GetMasterVolume gave wrong error: %08x\n", hr);

    hr = ISimpleAudioVolume_GetMasterVolume(sav, &vol);
    ok(hr == S_OK, "GetMasterVolume failed: %08x\n", hr);
    ok(vol == 1.f, "Master volume wasn't 1: %f\n", vol);

    hr = ISimpleAudioVolume_SetMasterVolume(sav, -1.f, NULL);
    ok(hr == E_INVALIDARG, "SetMasterVolume gave wrong error: %08x\n", hr);

    hr = ISimpleAudioVolume_SetMasterVolume(sav, 2.f, NULL);
    ok(hr == E_INVALIDARG, "SetMasterVolume gave wrong error: %08x\n", hr);

    hr = ISimpleAudioVolume_SetMasterVolume(sav, 0.2f, NULL);
    ok(hr == S_OK, "SetMasterVolume failed: %08x\n", hr);

    hr = ISimpleAudioVolume_GetMasterVolume(sav, &vol);
    ok(hr == S_OK, "GetMasterVolume failed: %08x\n", hr);
    ok(fabsf(vol - 0.2f) < 0.05f, "Master volume wasn't 0.2: %f\n", vol);

    hr = ISimpleAudioVolume_GetMute(sav, NULL);
    ok(hr == NULL_PTR_ERR, "GetMute gave wrong error: %08x\n", hr);

    mute = TRUE;
    hr = ISimpleAudioVolume_GetMute(sav, &mute);
    ok(hr == S_OK, "GetMute failed: %08x\n", hr);
    ok(mute == FALSE, "Session is already muted\n");

    hr = ISimpleAudioVolume_SetMute(sav, TRUE, NULL);
    ok(hr == S_OK, "SetMute failed: %08x\n", hr);

    mute = FALSE;
    hr = ISimpleAudioVolume_GetMute(sav, &mute);
    ok(hr == S_OK, "GetMute failed: %08x\n", hr);
    ok(mute == TRUE, "Session should have been muted\n");

    hr = ISimpleAudioVolume_GetMasterVolume(sav, &vol);
    ok(hr == S_OK, "GetMasterVolume failed: %08x\n", hr);
    ok(fabsf(vol - 0.2f) < 0.05f, "Master volume wasn't 0.2: %f\n", vol);

    hr = ISimpleAudioVolume_SetMasterVolume(sav, 1.f, NULL);
    ok(hr == S_OK, "SetMasterVolume failed: %08x\n", hr);

    mute = FALSE;
    hr = ISimpleAudioVolume_GetMute(sav, &mute);
    ok(hr == S_OK, "GetMute failed: %08x\n", hr);
    ok(mute == TRUE, "Session should have been muted\n");

    hr = ISimpleAudioVolume_SetMute(sav, FALSE, NULL);
    ok(hr == S_OK, "SetMute failed: %08x\n", hr);

    ISimpleAudioVolume_Release(sav);
    IAudioClient_Release(ac);
    CoTaskMemFree(fmt);
}