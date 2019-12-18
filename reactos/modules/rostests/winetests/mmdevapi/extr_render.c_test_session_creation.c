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
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  int /*<<< orphan*/  IAudioSessionManager ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  AUDCLNT_STREAMFLAGS_NOPERSIST ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoCreateGuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IAudioClient_GetMixFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IAudioClient_GetService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IAudioClient_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioSessionManager_GetSimpleAudioVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IAudioSessionManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  IID_IAudioSessionManager ; 
 int /*<<< orphan*/  IID_ISimpleAudioVolume ; 
 scalar_t__ IMMDeviceEnumerator_GetDefaultAudioEndpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IMMDevice_Activate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMMDevice_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ISimpleAudioVolume_GetMasterVolume (int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  ISimpleAudioVolume_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ISimpleAudioVolume_SetMasterVolume (int /*<<< orphan*/ *,float,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * dev ; 
 int /*<<< orphan*/  eCapture ; 
 int /*<<< orphan*/  eMultimedia ; 
 float fabs (float) ; 
 int /*<<< orphan*/  mme ; 
 int /*<<< orphan*/  ok (int,char*,float) ; 

__attribute__((used)) static void test_session_creation(void)
{
    IMMDevice *cap_dev;
    IAudioClient *ac;
    IAudioSessionManager *sesm;
    ISimpleAudioVolume *sav;
    GUID session_guid;
    float vol;
    HRESULT hr;
    WAVEFORMATEX *fmt;

    CoCreateGuid(&session_guid);

    hr = IMMDevice_Activate(dev, &IID_IAudioSessionManager,
            CLSCTX_INPROC_SERVER, NULL, (void**)&sesm);
    ok((hr == S_OK)^(sesm == NULL), "Activate %08x &out pointer\n", hr);
    ok(hr == S_OK, "Activate failed: %08x\n", hr);

    hr = IAudioSessionManager_GetSimpleAudioVolume(sesm, &session_guid,
            FALSE, &sav);
    ok(hr == S_OK, "GetSimpleAudioVolume failed: %08x\n", hr);

    hr = ISimpleAudioVolume_SetMasterVolume(sav, 0.6f, NULL);
    ok(hr == S_OK, "SetMasterVolume failed: %08x\n", hr);

    /* Release completely to show session persistence */
    ISimpleAudioVolume_Release(sav);
    IAudioSessionManager_Release(sesm);

    /* test if we can create a capture audioclient in the session we just
     * created from a SessionManager derived from a render device */
    hr = IMMDeviceEnumerator_GetDefaultAudioEndpoint(mme, eCapture,
            eMultimedia, &cap_dev);
    if(hr == S_OK){
        WAVEFORMATEX *cap_pwfx;
        IAudioClient *cap_ac;
        ISimpleAudioVolume *cap_sav;
        IAudioSessionManager *cap_sesm;

        hr = IMMDevice_Activate(cap_dev, &IID_IAudioSessionManager,
                CLSCTX_INPROC_SERVER, NULL, (void**)&cap_sesm);
        ok((hr == S_OK)^(cap_sesm == NULL), "Activate %08x &out pointer\n", hr);
        ok(hr == S_OK, "Activate failed: %08x\n", hr);

        hr = IAudioSessionManager_GetSimpleAudioVolume(cap_sesm, &session_guid,
                FALSE, &cap_sav);
        ok(hr == S_OK, "GetSimpleAudioVolume failed: %08x\n", hr);

        vol = 0.5f;
        hr = ISimpleAudioVolume_GetMasterVolume(cap_sav, &vol);
        ok(hr == S_OK, "GetMasterVolume failed: %08x\n", hr);

        ISimpleAudioVolume_Release(cap_sav);
        IAudioSessionManager_Release(cap_sesm);

        hr = IMMDevice_Activate(cap_dev, &IID_IAudioClient,
                CLSCTX_INPROC_SERVER, NULL, (void**)&cap_ac);
        ok(hr == S_OK, "Activate failed: %08x\n", hr);

        IMMDevice_Release(cap_dev);

        hr = IAudioClient_GetMixFormat(cap_ac, &cap_pwfx);
        ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

        hr = IAudioClient_Initialize(cap_ac, AUDCLNT_SHAREMODE_SHARED,
                0, 5000000, 0, cap_pwfx, &session_guid);
        ok(hr == S_OK, "Initialize failed: %08x\n", hr);

        CoTaskMemFree(cap_pwfx);

        if(hr == S_OK){
            hr = IAudioClient_GetService(cap_ac, &IID_ISimpleAudioVolume,
                    (void**)&cap_sav);
            ok(hr == S_OK, "GetService failed: %08x\n", hr);
        }
        if(hr == S_OK){
            vol = 0.5f;
            hr = ISimpleAudioVolume_GetMasterVolume(cap_sav, &vol);
            ok(hr == S_OK, "GetMasterVolume failed: %08x\n", hr);

            ISimpleAudioVolume_Release(cap_sav);
        }

        IAudioClient_Release(cap_ac);
    }

    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok((hr == S_OK)^(ac == NULL), "Activate %08x &out pointer\n", hr);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &fmt);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED,
            AUDCLNT_STREAMFLAGS_NOPERSIST, 5000000, 0, fmt, &session_guid);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);

    hr = IAudioClient_GetService(ac, &IID_ISimpleAudioVolume, (void**)&sav);
    ok(hr == S_OK, "GetService failed: %08x\n", hr);
    if(hr == S_OK){
        vol = 0.5f;
        hr = ISimpleAudioVolume_GetMasterVolume(sav, &vol);
        ok(hr == S_OK, "GetMasterVolume failed: %08x\n", hr);
        ok(fabs(vol - 0.6f) < 0.05f, "Got wrong volume: %f\n", vol);

        ISimpleAudioVolume_Release(sav);
    }

    CoTaskMemFree(fmt);
    IAudioClient_Release(ac);
}