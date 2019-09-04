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
typedef  int /*<<< orphan*/  IAudioEndpointVolume ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_POINTER ; 
 scalar_t__ IAudioEndpointVolume_GetMasterVolumeLevel (int /*<<< orphan*/ *,float*) ; 
 scalar_t__ IAudioEndpointVolume_GetMute (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioEndpointVolume_GetVolumeRange (int /*<<< orphan*/ *,float*,float*,float*) ; 
 int /*<<< orphan*/  IAudioEndpointVolume_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioEndpointVolume_SetMasterVolumeLevel (int /*<<< orphan*/ *,float,int /*<<< orphan*/ *) ; 
 scalar_t__ IAudioEndpointVolume_SetMute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioEndpointVolume ; 
 scalar_t__ IMMDevice_Activate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,float,float,float) ; 

__attribute__((used)) static void test_endpointvolume(void)
{
    HRESULT hr;
    IAudioEndpointVolume *aev;
    float mindb, maxdb, increment, volume;
    BOOL mute;

    hr = IMMDevice_Activate(dev, &IID_IAudioEndpointVolume,
            CLSCTX_INPROC_SERVER, NULL, (void**)&aev);
    ok(hr == S_OK, "Activation failed with %08x\n", hr);
    if(hr != S_OK)
        return;

    hr = IAudioEndpointVolume_GetVolumeRange(aev, &mindb, NULL, NULL);
    ok(hr == E_POINTER, "GetVolumeRange should have failed with E_POINTER: 0x%08x\n", hr);

    hr = IAudioEndpointVolume_GetVolumeRange(aev, &mindb, &maxdb, &increment);
    ok(hr == S_OK, "GetVolumeRange failed: 0x%08x\n", hr);
    trace("got range: [%f,%f]/%f\n", mindb, maxdb, increment);

    hr = IAudioEndpointVolume_SetMasterVolumeLevel(aev, mindb - increment, NULL);
    ok(hr == E_INVALIDARG, "SetMasterVolumeLevel failed: 0x%08x\n", hr);

    hr = IAudioEndpointVolume_GetMasterVolumeLevel(aev, &volume);
    ok(hr == S_OK, "GetMasterVolumeLevel failed: 0x%08x\n", hr);

    hr = IAudioEndpointVolume_SetMasterVolumeLevel(aev, volume, NULL);
    ok(hr == S_OK, "SetMasterVolumeLevel failed: 0x%08x\n", hr);

    hr = IAudioEndpointVolume_GetMute(aev, &mute);
    ok(hr == S_OK, "GetMute failed: %08x\n", hr);

    hr = IAudioEndpointVolume_SetMute(aev, mute, NULL);
    ok(hr == S_OK || hr == S_FALSE, "SetMute failed: %08x\n", hr);

    IAudioEndpointVolume_Release(aev);
}