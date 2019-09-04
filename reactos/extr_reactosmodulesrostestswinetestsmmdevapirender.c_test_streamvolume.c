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
struct TYPE_5__ {size_t nChannels; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  IAudioStreamVolume ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  float HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_1__*) ; 
 float E_INVALIDARG ; 
 float E_POINTER ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 float* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 float IAudioClient_GetMixFormat (int /*<<< orphan*/ *,TYPE_1__**) ; 
 float IAudioClient_GetService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 float IAudioClient_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ *) ; 
 float IAudioStreamVolume_GetAllVolumes (int /*<<< orphan*/ *,int,float*) ; 
 float IAudioStreamVolume_GetChannelCount (int /*<<< orphan*/ *,size_t*) ; 
 float IAudioStreamVolume_GetChannelVolume (int /*<<< orphan*/ *,size_t,float*) ; 
 int /*<<< orphan*/  IAudioStreamVolume_Release (int /*<<< orphan*/ *) ; 
 float IAudioStreamVolume_SetAllVolumes (int /*<<< orphan*/ *,int,float*) ; 
 float IAudioStreamVolume_SetChannelVolume (int /*<<< orphan*/ *,size_t,float) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  IID_IAudioStreamVolume ; 
 float IMMDevice_Activate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 float S_OK ; 
 int /*<<< orphan*/  dev ; 
 float fabsf (float) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_streamvolume(void)
{
    IAudioClient *ac;
    IAudioStreamVolume *asv;
    WAVEFORMATEX *fmt;
    UINT32 chans, i;
    HRESULT hr;
    float vol, *vols;

    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &fmt);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED, 0, 5000000,
            0, fmt, NULL);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);

    if(hr == S_OK){
        hr = IAudioClient_GetService(ac, &IID_IAudioStreamVolume, (void**)&asv);
        ok(hr == S_OK, "GetService failed: %08x\n", hr);
    }
    if(hr != S_OK){
        IAudioClient_Release(ac);
        CoTaskMemFree(fmt);
        return;
    }

    hr = IAudioStreamVolume_GetChannelCount(asv, NULL);
    ok(hr == E_POINTER, "GetChannelCount gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_GetChannelCount(asv, &chans);
    ok(hr == S_OK, "GetChannelCount failed: %08x\n", hr);
    ok(chans == fmt->nChannels, "GetChannelCount gave wrong number of channels: %d\n", chans);

    hr = IAudioStreamVolume_GetChannelVolume(asv, fmt->nChannels, NULL);
    ok(hr == E_POINTER, "GetChannelCount gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_GetChannelVolume(asv, fmt->nChannels, &vol);
    ok(hr == E_INVALIDARG, "GetChannelCount gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_GetChannelVolume(asv, 0, NULL);
    ok(hr == E_POINTER, "GetChannelCount gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_GetChannelVolume(asv, 0, &vol);
    ok(hr == S_OK, "GetChannelCount failed: %08x\n", hr);
    ok(vol == 1.f, "Channel volume was not 1: %f\n", vol);

    hr = IAudioStreamVolume_SetChannelVolume(asv, fmt->nChannels, -1.f);
    ok(hr == E_INVALIDARG, "SetChannelVolume gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_SetChannelVolume(asv, 0, -1.f);
    ok(hr == E_INVALIDARG, "SetChannelVolume gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_SetChannelVolume(asv, 0, 2.f);
    ok(hr == E_INVALIDARG, "SetChannelVolume gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_SetChannelVolume(asv, 0, 0.2f);
    ok(hr == S_OK, "SetChannelVolume failed: %08x\n", hr);

    hr = IAudioStreamVolume_GetChannelVolume(asv, 0, &vol);
    ok(hr == S_OK, "GetChannelCount failed: %08x\n", hr);
    ok(fabsf(vol - 0.2f) < 0.05f, "Channel volume wasn't 0.2: %f\n", vol);

    hr = IAudioStreamVolume_GetAllVolumes(asv, 0, NULL);
    ok(hr == E_POINTER, "GetAllVolumes gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_GetAllVolumes(asv, fmt->nChannels, NULL);
    ok(hr == E_POINTER, "GetAllVolumes gave wrong error: %08x\n", hr);

    vols = HeapAlloc(GetProcessHeap(), 0, fmt->nChannels * sizeof(float));
    ok(vols != NULL, "HeapAlloc failed\n");

    hr = IAudioStreamVolume_GetAllVolumes(asv, fmt->nChannels - 1, vols);
    ok(hr == E_INVALIDARG, "GetAllVolumes gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_GetAllVolumes(asv, fmt->nChannels, vols);
    ok(hr == S_OK, "GetAllVolumes failed: %08x\n", hr);
    ok(fabsf(vols[0] - 0.2f) < 0.05f, "Channel 0 volume wasn't 0.2: %f\n", vol);
    for(i = 1; i < fmt->nChannels; ++i)
        ok(vols[i] == 1.f, "Channel %d volume is not 1: %f\n", i, vols[i]);

    hr = IAudioStreamVolume_SetAllVolumes(asv, 0, NULL);
    ok(hr == E_POINTER, "SetAllVolumes gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_SetAllVolumes(asv, fmt->nChannels, NULL);
    ok(hr == E_POINTER, "SetAllVolumes gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_SetAllVolumes(asv, fmt->nChannels - 1, vols);
    ok(hr == E_INVALIDARG, "SetAllVolumes gave wrong error: %08x\n", hr);

    hr = IAudioStreamVolume_SetAllVolumes(asv, fmt->nChannels, vols);
    ok(hr == S_OK, "SetAllVolumes failed: %08x\n", hr);

    HeapFree(GetProcessHeap(), 0, vols);
    IAudioStreamVolume_Release(asv);
    IAudioClient_Release(ac);
    CoTaskMemFree(fmt);
}