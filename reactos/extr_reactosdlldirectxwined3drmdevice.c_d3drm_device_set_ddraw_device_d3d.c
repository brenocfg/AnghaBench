#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct d3drm_device {int /*<<< orphan*/ * render_target; int /*<<< orphan*/ * device; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * ddraw; int /*<<< orphan*/  d3drm; } ;
typedef  int /*<<< orphan*/  desc ;
struct TYPE_3__ {int dwSize; int /*<<< orphan*/  dwHeight; int /*<<< orphan*/  dwWidth; } ;
typedef  int /*<<< orphan*/  IDirectDrawSurface ;
typedef  int /*<<< orphan*/  IDirectDraw ;
typedef  int /*<<< orphan*/  IDirect3DDevice2 ;
typedef  int /*<<< orphan*/  IDirect3DDevice ;
typedef  int /*<<< orphan*/  IDirect3D ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DDSURFACEDESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3DRMERR_BADOBJECT ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice2_GetRenderTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DDevice2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirect3DRM_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3D_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirectDrawSurface_GetSurfaceDesc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IDirectDrawSurface_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirect3DDevice2 ; 
 int /*<<< orphan*/  IID_IDirectDraw ; 
 int /*<<< orphan*/  IID_IDirectDrawSurface ; 

__attribute__((used)) static HRESULT d3drm_device_set_ddraw_device_d3d(struct d3drm_device *device, IDirect3D *d3d, IDirect3DDevice *d3d_device)
{
    IDirectDraw *ddraw;
    IDirectDrawSurface *surface;
    IDirect3DDevice2 *d3d_device2 = NULL;
    DDSURFACEDESC desc;
    HRESULT hr;

    /* AddRef these interfaces beforehand for the intentional leak on reinitialization. */
    if (FAILED(hr = IDirect3D_QueryInterface(d3d, &IID_IDirectDraw, (void **)&ddraw)))
        return hr;
    IDirect3DRM_AddRef(device->d3drm);
    IDirect3DDevice_AddRef(d3d_device);

    /* Fetch render target and get width/height from there */
    if (FAILED(hr = IDirect3DDevice_QueryInterface(d3d_device, &IID_IDirectDrawSurface, (void **)&surface)))
    {
        if (FAILED(hr = IDirect3DDevice_QueryInterface(d3d_device, &IID_IDirect3DDevice2, (void **)&d3d_device2)))
            return hr;
        hr = IDirect3DDevice2_GetRenderTarget(d3d_device2, &surface);
        IDirect3DDevice2_Release(d3d_device2);
        if (FAILED(hr))
            return hr;
    }

    if (device->ddraw)
    {
        if (d3d_device2)
            IDirectDrawSurface_Release(surface);
        return D3DRMERR_BADOBJECT;
    }

    desc.dwSize = sizeof(desc);
    hr = IDirectDrawSurface_GetSurfaceDesc(surface, &desc);
    if (FAILED(hr))
    {
        IDirectDrawSurface_Release(surface);
        return hr;
    }

    device->ddraw = ddraw;
    device->width = desc.dwWidth;
    device->height = desc.dwHeight;
    device->device = d3d_device;
    device->render_target = surface;

    return hr;
}