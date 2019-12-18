#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_15__ {scalar_t__ use_ex; } ;
struct TYPE_18__ {int /*<<< orphan*/  BufferFormat; int /*<<< orphan*/  dev; int /*<<< orphan*/  devex; } ;
struct TYPE_17__ {TYPE_12__ hd3d; TYPE_3__ d3d_dev; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  video_format_t ;
typedef  TYPE_3__ d3d9_device_t ;
struct TYPE_19__ {int /*<<< orphan*/  BackBufferFormat; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ D3DPRESENT_PARAMETERS ;

/* Variables and functions */
 scalar_t__ D3D9_FillPresentationParameters (TYPE_12__*,TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ Direct3D9CreateResources (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Direct3D9DestroyResources (TYPE_1__*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9Ex_ResetEx (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_Reset (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 

__attribute__((used)) static int Direct3D9Reset(vout_display_t *vd, const video_format_t *fmtp)
{
    vout_display_sys_t *sys = vd->sys;
    d3d9_device_t *p_d3d9_dev = &sys->d3d_dev;

    D3DPRESENT_PARAMETERS d3dpp;
    if (D3D9_FillPresentationParameters(&sys->hd3d, p_d3d9_dev, &d3dpp))
    {
        msg_Err(vd, "Could not presentation parameters to reset device");
        return VLC_EGENERIC;
    }

    /* release all D3D objects */
    Direct3D9DestroyResources(vd);

    /* */
    HRESULT hr;
    if (sys->hd3d.use_ex){
        hr = IDirect3DDevice9Ex_ResetEx(p_d3d9_dev->devex, &d3dpp, NULL);
    } else {
        hr = IDirect3DDevice9_Reset(p_d3d9_dev->dev, &d3dpp);
    }
    if (FAILED(hr)) {
        msg_Err(vd, "IDirect3DDevice9_Reset failed! (hr=0x%lX)", hr);
        return VLC_EGENERIC;
    }
    p_d3d9_dev->BufferFormat = d3dpp.BackBufferFormat;

    /* re-create them */
    if (Direct3D9CreateResources(vd, fmtp)) {
        msg_Dbg(vd, "Direct3D9CreateResources failed !");
        return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}