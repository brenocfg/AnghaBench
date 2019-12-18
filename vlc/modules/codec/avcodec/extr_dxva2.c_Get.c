#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ vlc_va_t ;
struct TYPE_16__ {int /*<<< orphan*/  va_pool; int /*<<< orphan*/  device; int /*<<< orphan*/  devmng; } ;
typedef  TYPE_4__ vlc_va_sys_t ;
typedef  int /*<<< orphan*/  vlc_va_surface_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {int /*<<< orphan*/ * context; } ;
typedef  TYPE_5__ picture_t ;
struct TYPE_13__ {scalar_t__ surface; } ;
struct TYPE_14__ {TYPE_1__ picsys; } ;
struct TYPE_12__ {TYPE_2__ ctx; } ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DXVA2_E_NEW_VIDEO_DEVICE ; 
 TYPE_11__* DXVA2_PICCONTEXT_FROM_PICCTX (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IDirect3DDeviceManager9_TestDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewSurfacePicContext (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOITEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * va_pool_Get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_surface_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Get(vlc_va_t *va, picture_t *pic, uint8_t **data)
{
    vlc_va_sys_t *sys = va->sys;

    /* Check the device */
    HRESULT hr = IDirect3DDeviceManager9_TestDevice(sys->devmng, sys->device);
    if (FAILED(hr)) {
        if (hr == DXVA2_E_NEW_VIDEO_DEVICE)
            msg_Warn(va, "New video device detected.");
        else
            msg_Err(va, "device not usable. (hr=0x%lX)", hr);
        return VLC_EGENERIC;
    }

    vlc_va_surface_t *va_surface = va_pool_Get(sys->va_pool);
    if (unlikely(va_surface==NULL))
        return VLC_ENOITEM;

    pic->context = NewSurfacePicContext(va, va_surface);
    if (unlikely(pic->context == NULL))
    {
        va_surface_Release(va_surface);
        return VLC_ENOITEM;
    }
    *data = (uint8_t*)DXVA2_PICCONTEXT_FROM_PICCTX(pic->context)->ctx.picsys.surface;
    return VLC_SUCCESS;
}