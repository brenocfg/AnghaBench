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
typedef  int /*<<< orphan*/  surface_desc ;
struct d3drm_device {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * device; int /*<<< orphan*/ * render_target; int /*<<< orphan*/  d3drm; int /*<<< orphan*/ * ddraw; } ;
typedef  int /*<<< orphan*/  desc ;
typedef  int UINT ;
struct TYPE_12__ {int member_0; } ;
struct TYPE_10__ {int dwZBufferBitDepth; } ;
struct TYPE_9__ {int dwCaps; } ;
struct TYPE_11__ {int dwSize; int dwFlags; int /*<<< orphan*/  dwHeight; int /*<<< orphan*/  dwWidth; TYPE_2__ u2; TYPE_1__ ddsCaps; } ;
typedef  int /*<<< orphan*/  IDirectDrawSurface ;
typedef  int /*<<< orphan*/  IDirectDraw ;
typedef  int /*<<< orphan*/  IDirect3DDevice2 ;
typedef  int /*<<< orphan*/  IDirect3DDevice ;
typedef  int /*<<< orphan*/  IDirect3D2 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ DDSURFACEDESC ;
typedef  TYPE_4__ DDSCAPS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DDERR_INVALIDCAPS ; 
 int DDSCAPS_3DDEVICE ; 
 int DDSCAPS_ZBUFFER ; 
 int DDSD_CAPS ; 
 int DDSD_HEIGHT ; 
 int DDSD_WIDTH ; 
 int DDSD_ZBUFFERBITDEPTH ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IDirect3D2_CreateDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3D2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirect3DDevice2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DRM_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectDrawSurface_AddAttachedSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectDrawSurface_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectDrawSurface_DeleteAttachedSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectDrawSurface_GetAttachedSurface (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirectDrawSurface_GetSurfaceDesc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  IDirectDrawSurface_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirectDrawSurface_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectDraw_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectDraw_CreateSurface (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectDraw_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDirect3D2 ; 
 int /*<<< orphan*/  IID_IDirect3DDevice ; 
 int /*<<< orphan*/  IID_IDirect3DRGBDevice ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

HRESULT d3drm_device_init(struct d3drm_device *device, UINT version, IDirectDraw *ddraw, IDirectDrawSurface *surface,
            BOOL create_z_surface)
{
    DDSCAPS caps = { DDSCAPS_ZBUFFER };
    IDirectDrawSurface *ds = NULL;
    IDirect3DDevice *device1 = NULL;
    IDirect3DDevice2 *device2 = NULL;
    IDirect3D2 *d3d2 = NULL;
    DDSURFACEDESC desc, surface_desc;
    HRESULT hr;

    device->ddraw = ddraw;
    IDirectDraw_AddRef(ddraw);
    IDirect3DRM_AddRef(device->d3drm);
    device->render_target = surface;
    IDirectDrawSurface_AddRef(surface);

    desc.dwSize = sizeof(desc);
    hr = IDirectDrawSurface_GetSurfaceDesc(surface, &desc);
    if (FAILED(hr))
        return hr;

    if (!(desc.ddsCaps.dwCaps & DDSCAPS_3DDEVICE))
        return DDERR_INVALIDCAPS;

    hr = IDirectDrawSurface_GetAttachedSurface(surface, &caps, &ds);
    if (SUCCEEDED(hr))
    {
        create_z_surface = FALSE;
        IDirectDrawSurface_Release(ds);
        ds = NULL;
    }

    if (create_z_surface)
    {
        memset(&surface_desc, 0, sizeof(surface_desc));
        surface_desc.dwSize = sizeof(surface_desc);
        surface_desc.dwFlags = DDSD_CAPS | DDSD_ZBUFFERBITDEPTH | DDSD_WIDTH | DDSD_HEIGHT;
        surface_desc.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
        surface_desc.u2.dwZBufferBitDepth = 16;
        surface_desc.dwWidth = desc.dwWidth;
        surface_desc.dwHeight = desc.dwHeight;
        hr = IDirectDraw_CreateSurface(ddraw, &surface_desc, &ds, NULL);
        if (FAILED(hr))
            return hr;

        hr = IDirectDrawSurface_AddAttachedSurface(surface, ds);
        IDirectDrawSurface_Release(ds);
        if (FAILED(hr))
            return hr;
    }

    if (version == 1)
        hr = IDirectDrawSurface_QueryInterface(surface, &IID_IDirect3DRGBDevice, (void **)&device1);
    else
    {
        IDirectDraw_QueryInterface(ddraw, &IID_IDirect3D2, (void**)&d3d2);
        hr = IDirect3D2_CreateDevice(d3d2, &IID_IDirect3DRGBDevice, surface, &device2);
        IDirect3D2_Release(d3d2);
    }
    if (FAILED(hr))
    {
        IDirectDrawSurface_DeleteAttachedSurface(surface, 0, ds);
        return hr;
    }

    if (version != 1)
    {
        hr = IDirect3DDevice2_QueryInterface(device2, &IID_IDirect3DDevice, (void**)&device1);
        IDirect3DDevice2_Release(device2);
        if (FAILED(hr))
        {
            IDirectDrawSurface_DeleteAttachedSurface(surface, 0, ds);
            return hr;
        }
    }
    device->device = device1;
    device->width = desc.dwWidth;
    device->height = desc.dwHeight;

    return hr;
}