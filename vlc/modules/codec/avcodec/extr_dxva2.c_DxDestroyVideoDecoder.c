#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int surface_count; scalar_t__ decoder; } ;
struct TYPE_5__ {scalar_t__ dxva2_dll; int /*<<< orphan*/  hd3d; int /*<<< orphan*/  d3d_dev; int /*<<< orphan*/  devmng; int /*<<< orphan*/  d3ddec; int /*<<< orphan*/  device; scalar_t__* hw_surface; TYPE_1__ hw; } ;
typedef  TYPE_2__ vlc_va_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3D9_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D9_ReleaseDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  IDirect3DDeviceManager9_CloseDeviceHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDeviceManager9_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DSurface9_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirectXVideoDecoderService_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectXVideoDecoder_Release (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void DxDestroyVideoDecoder(void *opaque)
{
    vlc_va_sys_t *sys = opaque;
    /* releases a reference on each decoder surface */
    if (sys->hw.decoder)
        IDirectXVideoDecoder_Release(sys->hw.decoder);
    if (sys->hw_surface[0])
    {
        for (unsigned i = 0; i < sys->hw.surface_count; i++)
            IDirect3DSurface9_Release(sys->hw_surface[i]);
    }
    IDirect3DDeviceManager9_CloseDeviceHandle(sys->devmng, sys->device);
    IDirectXVideoDecoderService_Release(sys->d3ddec);
    IDirect3DDeviceManager9_Release(sys->devmng);
    D3D9_ReleaseDevice(&sys->d3d_dev);
    D3D9_Destroy( &sys->hd3d );
    if (sys->dxva2_dll)
        FreeLibrary(sys->dxva2_dll);

    free(sys);
}