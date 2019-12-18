#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ d3d9_handle_t ;
struct TYPE_11__ {int /*<<< orphan*/  adapterId; } ;
typedef  TYPE_2__ d3d9_device_t ;
struct TYPE_13__ {int /*<<< orphan*/  Format; } ;
struct TYPE_12__ {int BackBufferCount; void* BackBufferHeight; void* BackBufferWidth; int /*<<< orphan*/  BackBufferFormat; int /*<<< orphan*/  SwapEffect; int /*<<< orphan*/ * hDeviceWindow; int /*<<< orphan*/  EnableAutoDepthStencil; int /*<<< orphan*/  PresentationInterval; int /*<<< orphan*/  MultiSampleType; int /*<<< orphan*/  Windowed; int /*<<< orphan*/  Flags; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ D3DPRESENT_PARAMETERS ;
typedef  TYPE_4__ D3DDISPLAYMODE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DMULTISAMPLE_NONE ; 
 int /*<<< orphan*/  D3DPRESENTFLAG_VIDEO ; 
 int /*<<< orphan*/  D3DPRESENT_INTERVAL_DEFAULT ; 
 int /*<<< orphan*/  D3DSWAPEFFECT_COPY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 void* GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3D9_GetAdapterDisplayMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  SM_CXVIRTUALSCREEN ; 
 int /*<<< orphan*/  SM_CYVIRTUALSCREEN ; 
 int /*<<< orphan*/  TRUE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 

int D3D9_FillPresentationParameters(d3d9_handle_t *hd3d,
                                    const d3d9_device_t *d3ddev,
                                    D3DPRESENT_PARAMETERS *d3dpp)
{
    /*
    ** Get the current desktop display mode, so we can set up a back
    ** buffer of the same format
    */
    D3DDISPLAYMODE d3ddm;
    HRESULT hr = IDirect3D9_GetAdapterDisplayMode(hd3d->obj, d3ddev->adapterId, &d3ddm);
    if (FAILED(hr))
        return VLC_EGENERIC;

    /* Set up the structure used to create the D3DDevice. */
    ZeroMemory(d3dpp, sizeof(D3DPRESENT_PARAMETERS));
    d3dpp->Flags                  = D3DPRESENTFLAG_VIDEO;
    d3dpp->Windowed               = TRUE;
    d3dpp->MultiSampleType        = D3DMULTISAMPLE_NONE;
    d3dpp->PresentationInterval   = D3DPRESENT_INTERVAL_DEFAULT;
    d3dpp->EnableAutoDepthStencil = FALSE;
    d3dpp->hDeviceWindow          = NULL;
    d3dpp->SwapEffect             = D3DSWAPEFFECT_COPY;
    d3dpp->BackBufferFormat       = d3ddm.Format;
    d3dpp->BackBufferCount        = 1;
    d3dpp->BackBufferWidth        = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    d3dpp->BackBufferHeight       = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    return VLC_SUCCESS;
}