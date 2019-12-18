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
typedef  int /*<<< orphan*/  demux_t ;
typedef  int /*<<< orphan*/  IMMDeviceEnumerator ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  void IAudioClient ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  ERole ;
typedef  scalar_t__ EDataFlow ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  CLSID_MMDeviceEnumerator ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ GetDeviceFlow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  IID_IMMDeviceEnumerator ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_GetDefaultAudioEndpoint (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMMDevice_Activate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMMDevice_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ eCapture ; 
 int /*<<< orphan*/  eCommunications ; 
 int /*<<< orphan*/  eConsole ; 
 scalar_t__ eRender ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int var_InheritBool (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static IAudioClient *GetClient(demux_t *demux, bool *restrict loopbackp)
{
    IMMDeviceEnumerator *e;
    IMMDevice *dev;
    void *pv;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL,
                          &IID_IMMDeviceEnumerator, &pv);
    if (FAILED(hr))
    {
        msg_Err(demux, "cannot create device enumerator (error 0x%lX)", hr);
        return NULL;
    }
    e = pv;

    bool loopback = var_InheritBool(demux, "wasapi-loopback");
    EDataFlow flow = loopback ? eRender : eCapture;
    ERole role = loopback ? eConsole : eCommunications;

    hr = IMMDeviceEnumerator_GetDefaultAudioEndpoint(e, flow, role, &dev);
    IMMDeviceEnumerator_Release(e);
    if (FAILED(hr))
    {
        msg_Err(demux, "cannot get default device (error 0x%lX)", hr);
        return NULL;
    }

    hr = IMMDevice_Activate(dev, &IID_IAudioClient, CLSCTX_ALL, NULL, &pv);
    *loopbackp = GetDeviceFlow(dev) == eRender;
    IMMDevice_Release(dev);
    if (FAILED(hr))
        msg_Err(demux, "cannot activate device (error 0x%lX)", hr);
    return pv;
}