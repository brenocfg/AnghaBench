#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nChannels; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ISimpleAudioVolume ;
typedef  int /*<<< orphan*/  IChannelAudioVolume ;
typedef  int /*<<< orphan*/  IAudioStreamVolume ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  float HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  AUDCLNT_STREAMFLAGS_NOPERSIST ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 float CoCreateGuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_1__*) ; 
 float IAudioClient_GetMixFormat (int /*<<< orphan*/ *,TYPE_1__**) ; 
 float IAudioClient_GetService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 float IAudioClient_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ *) ; 
 float IAudioStreamVolume_GetChannelCount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float IAudioStreamVolume_GetChannelVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  IAudioStreamVolume_Release (int /*<<< orphan*/ *) ; 
 float IAudioStreamVolume_SetChannelVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float) ; 
 float IChannelAudioVolume_GetChannelCount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float IChannelAudioVolume_GetChannelVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  IChannelAudioVolume_Release (int /*<<< orphan*/ *) ; 
 float IChannelAudioVolume_SetChannelVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  IID_IAudioStreamVolume ; 
 int /*<<< orphan*/  IID_IChannelAudioVolume ; 
 int /*<<< orphan*/  IID_ISimpleAudioVolume ; 
 float IMMDevice_Activate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 float ISimpleAudioVolume_GetMasterVolume (int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  ISimpleAudioVolume_Release (int /*<<< orphan*/ *) ; 
 float ISimpleAudioVolume_SetMasterVolume (int /*<<< orphan*/ *,float,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (float) ; 
 float S_OK ; 
 int /*<<< orphan*/  dev ; 
 float fabsf (float) ; 
 int /*<<< orphan*/  ok (int,char*,float,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_volume_dependence(void)
{
    IAudioClient *ac, *ac2;
    ISimpleAudioVolume *sav;
    IChannelAudioVolume *cav;
    IAudioStreamVolume *asv;
    WAVEFORMATEX *fmt;
    HRESULT hr;
    float vol;
    GUID session;
    UINT32 nch;

    hr = CoCreateGuid(&session);
    ok(hr == S_OK, "CoCreateGuid failed: %08x\n", hr);

    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &fmt);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED,
            AUDCLNT_STREAMFLAGS_NOPERSIST, 5000000, 0, fmt, &session);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);

    hr = IAudioClient_GetService(ac, &IID_ISimpleAudioVolume, (void**)&sav);
    ok(hr == S_OK, "GetService (SimpleAudioVolume) failed: %08x\n", hr);

    hr = IAudioClient_GetService(ac, &IID_IChannelAudioVolume, (void**)&cav);
    ok(hr == S_OK, "GetService (ChannelAudioVolume) failed: %08x\n", hr);

    hr = IAudioClient_GetService(ac, &IID_IAudioStreamVolume, (void**)&asv);
    ok(hr == S_OK, "GetService (AudioStreamVolume) failed: %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioStreamVolume_SetChannelVolume(asv, 0, 0.2f);
    ok(hr == S_OK, "ASV_SetChannelVolume failed: %08x\n", hr);

    hr = IChannelAudioVolume_SetChannelVolume(cav, 0, 0.4f, NULL);
    ok(hr == S_OK, "CAV_SetChannelVolume failed: %08x\n", hr);

    hr = ISimpleAudioVolume_SetMasterVolume(sav, 0.6f, NULL);
    ok(hr == S_OK, "SAV_SetMasterVolume failed: %08x\n", hr);

    hr = IAudioStreamVolume_GetChannelVolume(asv, 0, &vol);
    ok(hr == S_OK, "ASV_GetChannelVolume failed: %08x\n", hr);
    ok(fabsf(vol - 0.2f) < 0.05f, "ASV_GetChannelVolume gave wrong volume: %f\n", vol);

    hr = IChannelAudioVolume_GetChannelVolume(cav, 0, &vol);
    ok(hr == S_OK, "CAV_GetChannelVolume failed: %08x\n", hr);
    ok(fabsf(vol - 0.4f) < 0.05f, "CAV_GetChannelVolume gave wrong volume: %f\n", vol);

    hr = ISimpleAudioVolume_GetMasterVolume(sav, &vol);
    ok(hr == S_OK, "SAV_GetMasterVolume failed: %08x\n", hr);
    ok(fabsf(vol - 0.6f) < 0.05f, "SAV_GetMasterVolume gave wrong volume: %f\n", vol);

    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac2);
    if(SUCCEEDED(hr)){
        IChannelAudioVolume *cav2;
        IAudioStreamVolume *asv2;

        hr = IAudioClient_Initialize(ac2, AUDCLNT_SHAREMODE_SHARED,
                AUDCLNT_STREAMFLAGS_NOPERSIST, 5000000, 0, fmt, &session);
        ok(hr == S_OK, "Initialize failed: %08x\n", hr);

        hr = IAudioClient_GetService(ac2, &IID_IChannelAudioVolume, (void**)&cav2);
        ok(hr == S_OK, "GetService failed: %08x\n", hr);

        hr = IAudioClient_GetService(ac2, &IID_IAudioStreamVolume, (void**)&asv2);
        ok(hr == S_OK, "GetService failed: %08x\n", hr);

        hr = IChannelAudioVolume_GetChannelVolume(cav2, 0, &vol);
        ok(hr == S_OK, "CAV_GetChannelVolume failed: %08x\n", hr);
        ok(fabsf(vol - 0.4f) < 0.05f, "CAV_GetChannelVolume gave wrong volume: %f\n", vol);

        hr = IAudioStreamVolume_GetChannelVolume(asv2, 0, &vol);
        ok(hr == S_OK, "ASV_GetChannelVolume failed: %08x\n", hr);
        ok(vol == 1.f, "ASV_GetChannelVolume gave wrong volume: %f\n", vol);

        hr = IChannelAudioVolume_GetChannelCount(cav2, &nch);
        ok(hr == S_OK, "GetChannelCount failed: %08x\n", hr);
        ok(nch == fmt->nChannels, "Got wrong channel count, expected %u: %u\n", fmt->nChannels, nch);

        hr = IAudioStreamVolume_GetChannelCount(asv2, &nch);
        ok(hr == S_OK, "GetChannelCount failed: %08x\n", hr);
        ok(nch == fmt->nChannels, "Got wrong channel count, expected %u: %u\n", fmt->nChannels, nch);

        IAudioStreamVolume_Release(asv2);
        IChannelAudioVolume_Release(cav2);
        IAudioClient_Release(ac2);
    }else
        skip("Unable to open the same device twice. Skipping session volume control tests\n");

    hr = IChannelAudioVolume_SetChannelVolume(cav, 0, 1.f, NULL);
    ok(hr == S_OK, "CAV_SetChannelVolume failed: %08x\n", hr);

    hr = ISimpleAudioVolume_SetMasterVolume(sav, 1.f, NULL);
    ok(hr == S_OK, "SAV_SetMasterVolume failed: %08x\n", hr);

    CoTaskMemFree(fmt);
    ISimpleAudioVolume_Release(sav);
    IChannelAudioVolume_Release(cav);
    IAudioStreamVolume_Release(asv);
    IAudioClient_Release(ac);
}