#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int owner; void* context_mutex; int /*<<< orphan*/ * d3ddevice; int /*<<< orphan*/  feature_level; int /*<<< orphan*/ * d3dcontext; } ;
typedef  TYPE_1__ d3d11_device_t ;
typedef  int /*<<< orphan*/  context_lock ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  ID3D11DeviceContext ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  void* HANDLE ;

/* Variables and functions */
 int D3D11_CREATE_DEVICE_VIDEO_SUPPORT ; 
 int /*<<< orphan*/  D3D11_GetDriverVersion (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  GUID_CONTEXT_MUTEX ; 
 int /*<<< orphan*/  ID3D11DeviceContext_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_GetDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_GetPrivateData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,void**) ; 
 int ID3D11Device_GetCreationFlags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_GetFeatureLevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Device_Release (int /*<<< orphan*/ *) ; 
 void* INVALID_HANDLE_VALUE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

HRESULT D3D11_CreateDeviceExternal(vlc_object_t *obj, ID3D11DeviceContext *d3d11ctx,
                                   bool hw_decoding, d3d11_device_t *out)
{
    HRESULT hr;
    ID3D11DeviceContext_GetDevice( d3d11ctx, &out->d3ddevice );

    if (hw_decoding)
    {
        UINT creationFlags = ID3D11Device_GetCreationFlags(out->d3ddevice);
        if (!(creationFlags & D3D11_CREATE_DEVICE_VIDEO_SUPPORT))
        {
            msg_Err(obj, "the provided D3D11 device doesn't support decoding");
            ID3D11Device_Release(out->d3ddevice);
            out->d3ddevice = NULL;
            return E_FAIL;
        }
    }

    ID3D11DeviceContext_AddRef( d3d11ctx );
    out->d3dcontext = d3d11ctx;
    out->owner = false;
    out->feature_level = ID3D11Device_GetFeatureLevel(out->d3ddevice );

    HANDLE context_lock = INVALID_HANDLE_VALUE;
    UINT dataSize = sizeof(context_lock);
    hr = ID3D11DeviceContext_GetPrivateData(d3d11ctx, &GUID_CONTEXT_MUTEX, &dataSize, &context_lock);
    if (SUCCEEDED(hr))
        out->context_mutex = context_lock;
    else
        out->context_mutex = INVALID_HANDLE_VALUE;

    D3D11_GetDriverVersion(obj, out);
    return S_OK;
}