#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ cbSize; } ;
typedef  TYPE_3__ WAVEFORMATEX ;
struct TYPE_16__ {int /*<<< orphan*/  (* pGetAudioEndpoint ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  flow; int /*<<< orphan*/  devguid; int /*<<< orphan*/  IMMDevice_iface; } ;
struct TYPE_11__ {int /*<<< orphan*/ * pBlobData; scalar_t__ cbSize; } ;
struct TYPE_12__ {TYPE_1__ blob; } ;
struct TYPE_14__ {TYPE_2__ u; int /*<<< orphan*/  vt; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ PROPVARIANT ;
typedef  TYPE_5__ MMDevice ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (TYPE_3__*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAudioClient_GetMixFormat (int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  IAudioClient_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMDevice_SetPropValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  PKEY_AudioEngine_DeviceFormat ; 
 int /*<<< orphan*/  PKEY_AudioEngine_OEMFormat ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  VT_BLOB ; 
 int /*<<< orphan*/  VT_EMPTY ; 
 TYPE_7__ drvs ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT set_format(MMDevice *dev)
{
    HRESULT hr;
    IAudioClient *client;
    WAVEFORMATEX *fmt;
    PROPVARIANT pv = { VT_EMPTY };

    hr = drvs.pGetAudioEndpoint(&dev->devguid, &dev->IMMDevice_iface, &client);
    if(FAILED(hr))
        return hr;

    hr = IAudioClient_GetMixFormat(client, &fmt);
    if(FAILED(hr)){
        IAudioClient_Release(client);
        return hr;
    }

    IAudioClient_Release(client);

    pv.vt = VT_BLOB;
    pv.u.blob.cbSize = sizeof(WAVEFORMATEX) + fmt->cbSize;
    pv.u.blob.pBlobData = (BYTE*)fmt;
    MMDevice_SetPropValue(&dev->devguid, dev->flow,
            &PKEY_AudioEngine_DeviceFormat, &pv);
    MMDevice_SetPropValue(&dev->devguid, dev->flow,
            &PKEY_AudioEngine_OEMFormat, &pv);
    CoTaskMemFree(fmt);

    return S_OK;
}