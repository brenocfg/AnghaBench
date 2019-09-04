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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  ISimpleAudioVolume ;
typedef  int /*<<< orphan*/  IAudioStreamVolume ;
typedef  int /*<<< orphan*/  IAudioRenderClient ;
typedef  int /*<<< orphan*/  IAudioClock ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_GetMixFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IAudioClient_GetService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IAudioClient_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClient_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioClock_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioClock_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioRenderClient_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioRenderClient_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAudioStreamVolume_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioStreamVolume_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  IID_IAudioClock ; 
 int /*<<< orphan*/  IID_IAudioRenderClient ; 
 int /*<<< orphan*/  IID_IAudioStreamVolume ; 
 int /*<<< orphan*/  IID_ISimpleAudioVolume ; 
 scalar_t__ IMMDevice_Activate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ISimpleAudioVolume_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ ISimpleAudioVolume_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_references(void)
{
    IAudioClient *ac;
    IAudioRenderClient *rc;
    ISimpleAudioVolume *sav;
    IAudioStreamVolume *asv;
    IAudioClock *acl;
    WAVEFORMATEX *pwfx;
    HRESULT hr;
    ULONG ref;

    /* IAudioRenderClient */
    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &pwfx);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED, 0, 5000000,
            0, pwfx, NULL);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);

    CoTaskMemFree(pwfx);

    hr = IAudioClient_GetService(ac, &IID_IAudioRenderClient, (void**)&rc);
    ok(hr == S_OK, "GetService failed: %08x\n", hr);
    if(hr != S_OK) {
        IAudioClient_Release(ac);
        return;
    }

    IAudioRenderClient_AddRef(rc);
    ref = IAudioRenderClient_Release(rc);
    ok(ref != 0, "RenderClient_Release gave wrong refcount: %u\n", ref);

    ref = IAudioClient_Release(ac);
    ok(ref != 0, "Client_Release gave wrong refcount: %u\n", ref);

    ref = IAudioRenderClient_Release(rc);
    ok(ref == 0, "RenderClient_Release gave wrong refcount: %u\n", ref);

    /* ISimpleAudioVolume */
    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &pwfx);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED, 0, 5000000,
            0, pwfx, NULL);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);

    CoTaskMemFree(pwfx);

    hr = IAudioClient_GetService(ac, &IID_ISimpleAudioVolume, (void**)&sav);
    ok(hr == S_OK, "GetService failed: %08x\n", hr);

    ISimpleAudioVolume_AddRef(sav);
    ref = ISimpleAudioVolume_Release(sav);
    ok(ref != 0, "SimpleAudioVolume_Release gave wrong refcount: %u\n", ref);

    ref = IAudioClient_Release(ac);
    ok(ref != 0, "Client_Release gave wrong refcount: %u\n", ref);

    ref = ISimpleAudioVolume_Release(sav);
    ok(ref == 0, "SimpleAudioVolume_Release gave wrong refcount: %u\n", ref);

    /* IAudioClock */
    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &pwfx);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED, 0, 5000000,
            0, pwfx, NULL);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);

    CoTaskMemFree(pwfx);

    hr = IAudioClient_GetService(ac, &IID_IAudioClock, (void**)&acl);
    ok(hr == S_OK, "GetService failed: %08x\n", hr);

    IAudioClock_AddRef(acl);
    ref = IAudioClock_Release(acl);
    ok(ref != 0, "AudioClock_Release gave wrong refcount: %u\n", ref);

    ref = IAudioClient_Release(ac);
    ok(ref != 0, "Client_Release gave wrong refcount: %u\n", ref);

    ref = IAudioClock_Release(acl);
    ok(ref == 0, "AudioClock_Release gave wrong refcount: %u\n", ref);

    /* IAudioStreamVolume */
    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_INPROC_SERVER,
            NULL, (void**)&ac);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioClient_GetMixFormat(ac, &pwfx);
    ok(hr == S_OK, "GetMixFormat failed: %08x\n", hr);

    hr = IAudioClient_Initialize(ac, AUDCLNT_SHAREMODE_SHARED, 0, 5000000,
            0, pwfx, NULL);
    ok(hr == S_OK, "Initialize failed: %08x\n", hr);

    CoTaskMemFree(pwfx);

    hr = IAudioClient_GetService(ac, &IID_IAudioStreamVolume, (void**)&asv);
    ok(hr == S_OK, "GetService failed: %08x\n", hr);

    IAudioStreamVolume_AddRef(asv);
    ref = IAudioStreamVolume_Release(asv);
    ok(ref != 0, "AudioStreamVolume_Release gave wrong refcount: %u\n", ref);

    ref = IAudioClient_Release(ac);
    ok(ref != 0, "Client_Release gave wrong refcount: %u\n", ref);

    ref = IAudioStreamVolume_Release(asv);
    ok(ref == 0, "AudioStreamVolume_Release gave wrong refcount: %u\n", ref);
}