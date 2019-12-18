#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ d3d9_handle_t ;
struct TYPE_10__ {int owner; int /*<<< orphan*/  BufferFormat; int /*<<< orphan*/ * dev; int /*<<< orphan*/  adapterId; int /*<<< orphan*/  caps; } ;
typedef  TYPE_2__ d3d9_device_t ;
struct TYPE_12__ {int /*<<< orphan*/  DeviceType; int /*<<< orphan*/  AdapterOrdinal; } ;
struct TYPE_11__ {int /*<<< orphan*/  Format; } ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ D3DDISPLAYMODE ;
typedef  TYPE_4__ D3DDEVICE_CREATION_PARAMETERS ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3D9_GetAdapterDisplayMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IDirect3D9_GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_GetCreationParameters (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 

HRESULT D3D9_CreateDeviceExternal(IDirect3DDevice9 *dev, d3d9_handle_t *hd3d,
                                  d3d9_device_t *out)
{
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr = IDirect3DDevice9_GetCreationParameters(dev, &params);
    if (FAILED(hr))
       return hr;
    out->dev   = dev;
    out->owner = false;
    out->adapterId = params.AdapterOrdinal;
    ZeroMemory(&out->caps, sizeof(out->caps));
    hr = IDirect3D9_GetDeviceCaps(hd3d->obj, out->adapterId, params.DeviceType, &out->caps);
    if (FAILED(hr))
       return hr;
    D3DDISPLAYMODE d3ddm;
    hr = IDirect3D9_GetAdapterDisplayMode(hd3d->obj, out->adapterId, &d3ddm);
    if (FAILED(hr))
        return hr;
    IDirect3DDevice9_AddRef(out->dev);
    out->BufferFormat = d3ddm.Format;
    return S_OK;
}